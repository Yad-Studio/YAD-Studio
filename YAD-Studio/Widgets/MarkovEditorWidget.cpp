#include "MarkovEditorWidget.h"
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QTextBlock>

#include "Logic/MarkovParser.h"

MarkovEditorWidget::MarkovEditorWidget(QWidget *parent) :
    QPlainTextEdit(parent),
    _can_run(false),
    _last_source_code(""),
    m_countCache(-1, -1),
    _line_number_metrics(_line_number_font),
    _current_line(-1)
{
    connect(this, SIGNAL(textChanged()), this, SLOT(userChangedSourceCode()));

    //Set font
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);

    this->setFont(font);

    //Set tab width
    QFontMetrics metrics(font);
    this->setTabStopWidth(4 * metrics.width(' '));

    _line_number_font.setFamily("Courier");
    _line_number_font.setStyleHint(QFont::Monospace);
    _line_number_font.setFixedPitch(true);
    _line_number_font.setPointSize(11);

    _line_number_metrics = QFontMetrics(_line_number_font);

    //Line numbers
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth();
    highlightCurrentLine();
}

int MarkovEditorWidget::lineNumberAreaWidth()
{
    int digits = 3;
    int max = qMax(1, blockCount());
    max /= 100;

    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + _line_number_metrics.width(QLatin1Char('9')) * digits + 3;

    return space;
}

void MarkovEditorWidget::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void MarkovEditorWidget::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy) {
        lineNumberArea->scroll(0, dy);
    }
    else if (m_countCache.first != blockCount()
             || m_countCache.second != textCursor().block().lineCount()) {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
        m_countCache.first = blockCount();
        m_countCache.second = textCursor().block().lineCount();
    }

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();
}

void MarkovEditorWidget::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

int getLineNumber(QTextCursor cursor)
{
    cursor.movePosition(QTextCursor::StartOfLine);

    int lines = 1;
    while(cursor.positionInBlock()>0) {
        cursor.movePosition(QTextCursor::Up);
        lines++;
    }
    QTextBlock block = cursor.block().previous();

    while(block.isValid()) {
        lines += block.lineCount();
        block = block.previous();
    }
    return lines;
}

void MarkovEditorWidget::highlightCurrentLine()
{
    int current_line = getLineNumber(textCursor());
    if(_current_line != current_line)
    {
        _current_line = current_line;
        update();
    }

//    QList<QTextEdit::ExtraSelection> extraSelections;

//    if (!isReadOnly()) {
//        QTextEdit::ExtraSelection selection;

//        QColor lineColor = QColor(Qt::yellow).lighter(160);

//        selection.format.setBackground(lineColor);
//        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//        selection.cursor = textCursor();
//        selection.cursor.clearSelection();
//        extraSelections.append(selection);
//    }

//    setExtraSelections(extraSelections);
}


void MarkovEditorWidget::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPalette palette;

    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), palette.color(QPalette::Window));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();


    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            bool is_current_line = (_current_line == (blockNumber+1));

            QString number = QString::number(blockNumber + 1);
            painter.setPen(palette.color(QPalette::Dark));
            if(is_current_line)
            {
                _line_number_font.setBold(true);
                painter.setFont(_line_number_font);
                _line_number_font.setBold(false);
            }
            else
            {
                painter.setFont(_line_number_font);
            }
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}


MarkovEditorWidget::~MarkovEditorWidget()
{
}


void MarkovEditorWidget::newSourceCode(QString source_code, bool system_change)
{
    if(system_change)
    {
        _last_source_code = source_code;
    }
    this->setPlainText(source_code);
}

void MarkovEditorWidget::deleteSelection()
{
    QTextCursor cursor = this->textCursor();
    cursor.removeSelectedText();
    this->setTextCursor(cursor);
}
void MarkovEditorWidget::setCanRun(bool new_value)
{
    if(new_value != _can_run)
    {
        _can_run = new_value;
        emit canRun(_can_run);
    }
}

void MarkovEditorWidget::userChangedSourceCode()
{
    QString source_code = this->toPlainText();
    if(_last_source_code != source_code)
    {
        emit sourceCodeChanged(source_code);
    }

    _last_source_code = source_code;


    bool res = MarkovParser::parseSourceCode(source_code, _algorithm, _errors);

    if(res)
    {
        emit markovAlgorithmChanged(_algorithm);
        setCanRun(true);
    }
    else
    {
        setCanRun(false);
        updateErrors();
    }
}

void MarkovEditorWidget::updateErrors()
{
    for(int i=0; i<_errors.size(); ++i)
    {
        CompilerError err = _errors[i];
        qDebug() << "Error: " << err.getErrorNumber() << " line: " << err.getLineNumber() <<
                    "Title: " << err.getErrorTitle() << err.getErrorDescription();

    }
}
