#include "MarkovEditorWidget.h"
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include "Logic/MarkovParser.h"

MarkovEditorWidget::MarkovEditorWidget(QWidget *parent) :
    QPlainTextEdit(parent),
    _can_run(false),
    _last_source_code("")
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


    this->newSourceCode("//Alphabet\nT = {}\n\n//Rules\n//a -> b", true);
}

MarkovEditorWidget::~MarkovEditorWidget()
{
}


void MarkovEditorWidget::newSourceCode(QString source_code, bool user_change)
{
    if(!user_change)
        _last_source_code = source_code;
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
        _last_source_code = source_code;
        emit sourceCodeChanged(source_code);

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
