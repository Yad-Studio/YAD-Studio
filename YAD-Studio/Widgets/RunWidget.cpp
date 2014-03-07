#include "RunWidget.h"
#include "ui_RunWidget.h"
#include "QObject"
#include "algorithm"
#include "MarkovWordWidget.h"

RunWidget::RunWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunWidget)
{
    ui->setupUi(this);

    if(!isVisible())
    {
        //setVisible(true);
        show();
    }
    ui->outputWord->setVisible(false);

//    runFailed("abcd", RunError("Error My","Diff error",105),205);

//    runSuccess("ssrr","outputoutput",1234);

    ui->errorDescription->setVisible(false);
    ui->errorTitle->setVisible(false);

    ui->outputWord->setVisible(false);
    ui->outputWidget->setVisible(false);

    connect(ui->closeButton,
            SIGNAL(clicked()),
            this,
            SLOT(onCloseClicked()));
}

RunWidget::~RunWidget()
{
    delete ui;
}
void RunWidget::runStarted(QString input_word)
{
    ui->inputWidget->setWord(input_word);

    ui->errorDescription->setVisible(false);
    ui->errorTitle->setVisible(false);

    ui->outputWord->setVisible(false);
    ui->outputWidget->setVisible(false);
}

void RunWidget::runStepsMade(int steps_make)
{
    ui->stepsNumber->setText(QString::number(steps_make));
}

void RunWidget::runSuccess(QString input_word,
                QString output_word,
                int steps_made)
{
    ui->inputWidget->setWord(input_word);

    ui->stepsNumber->setVisible(true);
    ui->stepsNumber->setText(QString::number(steps_made));

    ui->outputWord->setVisible(true);
    ui->outputWidget->setVisible(true);
    ui->outputWord->setText("Output Word:");
    ui->outputWidget->setWord(output_word);

    ui->errorDescription->setVisible(false);
    ui->errorTitle->setVisible(false);
}

void RunWidget::runFailed(QString input_word,
               RunError error,
               int steps_made)
{
    ui->inputWidget->setWord(input_word);

    ui->stepsNumber->setVisible(true);
    ui->stepsNumber->setText(QString::number(steps_made));

    ui->errorDescription->setVisible(true);
    ui->errorTitle->setVisible(true);
    ui->errorTitle->setText("Error");
    //ui->errorDescription->setText(error.getFullErrorInfo());

    ui->errorDescription->setText(tr("<b>%1: %2</b><br>%3").arg(QString::number(error.getErrorNumber())).arg(error.getErrorTitle()).arg(error.getErrorDescription()));

    QPalette palette = ui->errorTitle->palette();
    palette.setColor(ui->errorTitle->foregroundRole(), Qt::red);
    ui->errorTitle->setPalette(palette);

    QPalette palette2 = ui->errorDescription->palette();
    palette2.setColor(ui->errorDescription->foregroundRole(), Qt::red);
    ui->errorDescription->setPalette(palette2);

    ui->outputWord->setVisible(false);
    ui->outputWidget->setVisible(false);
}
void RunWidget::onCloseClicked()
{
    //this->close();
    //setVisible(false);
    hide();
}
