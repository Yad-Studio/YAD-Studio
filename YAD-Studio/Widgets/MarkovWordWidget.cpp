#include "MarkovWordWidget.h"
#include "ui_MarkovWordWidget.h"

MarkovWordWidget::MarkovWordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkovWordWidget)
{
    ui->setupUi(this);

    //TODO: delete - it is only for testing
    //setWord("ababbba");
//    addHighlight(2,4,HighlightType::After);
//    removeHighlight();
//    addHighlight(2,8,HighlightType::After);
//    removeHighlight();
//    addHighlight(0,8,HighlightType::Before);
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
    QString text = ui->word->toPlainText();
    QString begin = text.left(from);
    QString middle = text.mid(from,length);
    QString end = text.mid(from+length,text.size());

    QString color = "\"green\"";
    if (type == Before)
        color = "\"red\"";


    QString text_code = "<font color="+color+">"+middle+"</font>";
    ui->word->setText(begin + text_code + end);

}

void MarkovWordWidget::removeHighlight()
{
    ui->word->setText(_word);
}
