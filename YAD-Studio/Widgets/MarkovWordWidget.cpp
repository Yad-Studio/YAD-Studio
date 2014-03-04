#include "MarkovWordWidget.h"
#include "ui_MarkovWordWidget.h"

MarkovWordWidget::MarkovWordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkovWordWidget)
{
    ui->setupUi(this);

    setWord("HelloWorldHelloWorldHelloWorldHelloWorldHelloWorldHelloWorld");
    addHighlight(2,4,HighlightType::After);
    removeHighlight();

    //addHighlight(2,4,HighlightType::After);
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

//    QPalette palette = ui->word->palette();
//    (palette,0,from);
//    palette.setColor(ui->word->foregroundRole(), Qt::green);
//    ui->word->setPalette(palette);
}

void MarkovWordWidget::removeHighlight()
{
    QString text = ui->word->text();
    QString result = find(text);

    //QString color = "\"black\"";
    //QString text_code = "<font color="+color+">"+text+"</font>";

    //ui->word->
    ui->word->setText(result);
}
QString MarkovWordWidget::find(QString source)
{
    //replace green or red --> black
    QString result ="";
    for(unsigned int i=0; i<source.size(); ++i)
    {
        if(source[i] == 'g' && i+4 != source.size())
        {
            if(source[i+1]=='r' && source[i+2]=='e' &&
                    source[i+3]=='e' && source[i+4]=='n')
            {
                result = source.mid(0,i);
                result += "black";
                result += source.mid(i+5,source.size());
                break;
            }
        }
        else if (source[i] == 'r' && i+2 != source.size())
        {
            if(source[i+1]=='e' && source[i+2] == 'd')
            {
                result = source.mid(0,i);
                result += "black";
                result += source.mid(i+3,source.size());
                break;
            }
        }
    }
    return result;
}
