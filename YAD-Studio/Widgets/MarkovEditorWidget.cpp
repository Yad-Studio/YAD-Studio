#include "MarkovEditorWidget.h"
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QTextBlock>

#include "Logic/MarkovParser.h"
static int break_point_width = 10;
static int break_point_padding = 3;

MarkovEditorWidget::MarkovEditorWidget(QWidget *parent) :
    QPlainTextEdit(parent),
    _can_run(false),
    _last_source_code(""),
    m_countCache(-1, -1),
    _line_number_metrics(_line_number_font),
    _current_line(-1),
    _highlighter(this),
    _highlighted_number(-1)
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
    lineNumberArea->setCursor(Qt::PointingHandCursor);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth();
    highlightCurrentLine();
}

MarkovEditorWidget::MarkovHighliter::MarkovHighliter(MarkovEditorWidget *editor)
    : QSyntaxHighlighter(editor->document()),
      _editor(editor)
{}

void MarkovEditorWidget::MarkovHighliter::highlightBlock(const QString& text)
{
    QColor comments_color(137, 137, 137);
    QColor alphabet_color(36,165,255);
    QColor system_symbol(0,128,0);
    QColor normal_rule(224,116,1);
    QColor final_rule(222,31,0);

    //Alphabet
    {
        QTextCharFormat symbols;
        symbols.setForeground(alphabet_color);
        symbols.setFontWeight(QFont::Bold);
        QString pattern = "["+QRegExp::escape(_editor->_algorithm.getAlphabet().getAllChars())+"]+";
        QRegExp expression(pattern);
        int index = text.indexOf(expression);
        while(index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, symbols);
            index = text.indexOf(expression, index + length);
        }
    }


    //System symbols
    {
        QTextCharFormat system;
        system.setForeground(system_symbol);
        system.setFontWeight(QFont::Bold);

        QString pattern = "[T= \\{\\},]+";
        QRegExp expression(pattern);
        int index = text.indexOf(expression);
        while(index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, system);
            index = text.indexOf(expression, index + length);
        }
    }

    //Rule
    {
        QTextCharFormat system;
        system.setForeground(normal_rule);
        system.setFontWeight(QFont::Bold);

        QString pattern = "->";
        QRegExp expression(pattern);
        int index = text.indexOf(expression);
        while(index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, system);
            index = text.indexOf(expression, index + length);
        }
    }

    //Final
    {
        QTextCharFormat system;
        system.setForeground(final_rule);
        system.setFontWeight(QFont::Bold);

        QString pattern = "->\\.";
        QRegExp expression(pattern);
        int index = text.indexOf(expression);
        while(index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, system);
            index = text.indexOf(expression, index + length);
        }
    }

    //Comments
    {
        QTextCharFormat comments;
        comments.setForeground(comments_color);
        comments.setFontItalic(true);

        QString pattern = "//.*$";
        QRegExp expression(pattern);
        int index = text.indexOf(expression);
        if(index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, comments);
        }
    }
}

int MarkovEditorWidget::lineNumberAreaWidth()
{
    int digits = 2;
    int max = qMax(1, blockCount());
    max /= 100;

    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = break_point_padding*2 + 3 + _line_number_metrics.width(QLatin1Char('9')) * digits + break_point_width;

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
    return cursor.block().blockNumber()+1;
}
void MarkovEditorWidget::showLineHighlight(int line_number)
{
    _highlighted_number = line_number;
    //removeLineHighlight();
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(216, 239, 255);

        QTextBlock block = document()->begin();

        int line = 1;
        while (block.isValid() && line < line_number)
        {
            block = block.next();
            line++;
        }

        if(block.isValid())
        {
            QTextCursor cursor(block);
            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = cursor;
            selection.cursor.clearSelection();
            extraSelections.append(selection);
        }
    }

    setExtraSelections(extraSelections);
    this->update();
}

void MarkovEditorWidget::removeLineHighlight()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    setExtraSelections(extraSelections);
}

void MarkovEditorWidget::highlightCurrentLine()
{
    int current_line = getLineNumber(textCursor());
    if(_current_line != current_line)
    {
        _current_line = current_line;
        update();
        notifyAboutCurrentLineErrors();
    }

}

int MarkovEditorWidget::getSelectedLines(QTextCursor cursor)
{
    int lines_number = 0;


    QTextBlock b1 = document()->findBlock(cursor.selectionStart());
    QTextBlock b2 = document()->findBlock(cursor.selectionEnd());

    for (QTextBlock block = b1;
         block.isValid() && b1 != b2;
         block = block.next())
    {
        lines_number += block.lineCount();
    }
    return lines_number;
}

void MarkovEditorWidget::keyPressEvent(QKeyEvent* e)
{

    bool ignore_event = false;
    if(e->key() == Qt::Key_Backtab
            || (e->key() == Qt::Key_Tab && e->modifiers() == Qt::ShiftModifier)
            )
    {
        qDebug() << "back tab";
        //e->ignore();
        QTextCursor cur = textCursor();

        int lines_number = getSelectedLines(cur);

        int start = cur.selectionStart();
        int end = cur.selectionEnd();

        if(lines_number == 0)
        {
            //One selection
            if(start == end && start > 0)
            {
                QChar cPrev = toPlainText().at(start-1);
                if(cPrev.isSpace())
                {
                    cur.deletePreviousChar();
                    cur.setPosition(start-1);
                    setTextCursor(cur);

                    setFocus();
                    ignore_event = true;
                }
            }
        }
        else
        {
            //Multiple lines
        }



    }

    if(ignore_event)
    {
        e->accept();
    }
    else
    {
        QPlainTextEdit::keyPressEvent(e);
    }
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
            int line_number = (blockNumber+1);
            bool is_current_line = (_current_line == line_number);
            bool is_break_point = (_breakpoints.find(line_number) != _breakpoints.end());

            bool is_error = (_lines_with_errors.find(line_number) != _lines_with_errors.end());

            if(is_error)
            {
                //painter.setBrush(QColor(255, 216, 216));
                QRect err(0, top, lineNumberArea->width(), bottom-top);
                painter.fillRect(err, QColor(255, 216, 216));
            }

            if(is_break_point)
            {
                float height = _line_number_metrics.height();

                QRectF bp(break_point_padding, top + (height-break_point_width) / 2,
                          break_point_width, break_point_width);

                if(_highlighted_number == line_number)
                {
                    QColor color(35, 164, 255);
                    painter.setBrush(color);
                    painter.setPen(color);
                }
                else
                {
                    painter.setBrush(Qt::red);
                    painter.setPen(Qt::red);
                }
                painter.drawEllipse(bp);
            }

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

void MarkovEditorWidget::breakPointPress(QMouseEvent* event)
{
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber() + 1;
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    int y = event->y();

    while(block.isValid() && y > bottom)
    {

        blockNumber++;
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
    }

    if(y > bottom)
    {
        blockNumber = -1;
    }

    if(blockNumber > 0)
        toggleBreakPoint(blockNumber);

}

void MarkovEditorWidget::toggleBreakPoint(int line_number)
{
    if(_breakpoints.find(line_number) == _breakpoints.end())
    {
        emit breakPointAdded(line_number);
        _breakpoints.insert(line_number);
        update();
    }
    else
    {
        emit breakPointRemoved(line_number);
        _breakpoints.remove(line_number);
        update();
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


    MarkovAlgorithm alg;
    bool res = MarkovParser::parseSourceCode(source_code, alg, _errors);

    bool rehighlight_needed = false;
    if(alg.getAlphabet().getAllChars() != _algorithm.getAlphabet().getAllChars())
        rehighlight_needed = true;

    _algorithm = alg;

    if(res)
    {

        emit markovAlgorithmChanged(_algorithm);
        setCanRun(true);
        updateErrors();


    }
    else
    {
        bool rehighlight_needed = false;
        if(alg.getAlphabet().getAllChars() != _algorithm.getAlphabet().getAllChars())
            rehighlight_needed = true;

        setCanRun(false);
        updateErrors();
    }

    if(rehighlight_needed)
        _highlighter.rehighlight();
}

void MarkovEditorWidget::updateErrors()
{
    _errors_map.clear();
    _lines_with_errors.clear();
    for(int i=0; i<_errors.size(); ++i)
    {

        CompilerError err = _errors[i];
        _lines_with_errors.insert(err.getLineNumber());

        if(_errors_map.find(err.getLineNumber()) != _errors_map.end())
        {
            _errors_map.insert(err.getLineNumber(), err);
        }
        //        qDebug() << "Error: " << err.getErrorNumber() << " line: " << err.getLineNumber() <<
        //                    "Title: " << err.getErrorTitle() << err.getErrorDescription();

    }
    update();
    notifyAboutCurrentLineErrors();

}

void MarkovEditorWidget::notifyAboutCurrentLineErrors()
{
    if(_lines_with_errors.find(_current_line) != _lines_with_errors.end())
    {
        emit lineFocusWithError(_current_line, _errors_map[_current_line]);
    }
    else
    {
        emit lineFocusWithoutError(_current_line);
    }
}
