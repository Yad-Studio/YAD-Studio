#include "MarkovWordWidget.h"
#include "ui_MarkovWordWidget.h"

MarkovWordWidget::MarkovWordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkovWordWidget)
{
    ui->setupUi(this);

    setWord("HelloWorld");
    addHighlight(2,4,HighlightType::After);
    removeHighlight();
}

MarkovWordWidget::~MarkovWordWidget()
{
    delete ui;
}
void MarkovWordWidget::setWord(const QString& word)
{
    _word = word;
    ui->word->setText(_word);
}

void MarkovWordWidget::addHighlight(int from,
                  int length,
                  HighlightType type)
{
    QString text = ui->word->text();
    QString begin = text.left(from);
    QString middle = text.mid(from,length);
    QString end = text.mid(from+length,text.size());

    QString color = "\"green\"";
    if (type == HighlightType::Before)
        color = "\"red\"";

    QString text_code = "<font color="+color+">"+middle+"</font>";

    ui->word->setText(begin + text_code + end);
}

void MarkovWordWidget::removeHighlight()
{
    QString text = ui->word->text();

    QString color = "\"black\"";
    QString text_code = "<font color="+color+">"+text+"</font>";
    ui->word->setText(text);
}
