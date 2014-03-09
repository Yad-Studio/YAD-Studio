#include "MarkovWordWidget.h"
#include "ui_MarkovWordWidget.h"
#include <QFontMetrics>
#include <QFont>

MarkovWordWidget::MarkovWordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkovWordWidget),
    _line_height(10)
{
    ui->setupUi(this);

    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(12);

    //_metrix = QFontMetrics(font);
    ui->word->setFont(font);

    QFontMetrics metrix(font);
    _line_height = metrix.height() + 10;
    ui->word->setMaximumHeight(_line_height);
    ui->word->setMinimumHeight(_line_height);
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
    if(_word.size() > 0)
        ui->word->setText(tr("<font color=#000>%1</font>").arg(_word));
    else
        ui->word->setText(tr("<font color=#777777>[empty]</font>"));
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
