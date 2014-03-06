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
    ui->outputWord->clear();

//    runFailed("abcd", RunError("Error My","Diff error",105),205);

//    runSuccess("ssrr","outputoutput",1234);

    ui->errorDescription->clear();
    ui->errorTitle->clear();

    ui->outputWord->clear();
    ui->outputWidget->close();

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

    ui->errorDescription->clear();
    ui->errorTitle->clear();

    ui->outputWord->clear();
    ui->outputWidget->close();
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
    ui->stepsNumber->setText(QString::number(steps_made));

    ui->outputWord->setText("Output Word:");
    ui->outputWidget->setWord(output_word);

    ui->errorDescription->clear();
    ui->errorTitle->clear();
}

void RunWidget::runFailed(QString input_word,
               RunError error,
               int steps_made)
{
    ui->inputWidget->setWord(input_word);
    ui->stepsNumber->setText(QString::number(steps_made));

    ui->errorTitle->setText("Error");
    ui->errorDescription->setText(error.getFullErrorInfo());

    QPalette palette = ui->errorTitle->palette();
    palette.setColor(ui->errorDescription->foregroundRole(), Qt::red);
    ui->errorTitle->setPalette(palette);

    QPalette palette2 = ui->errorDescription->palette();
    palette2.setColor(ui->errorDescription->foregroundRole(), Qt::red);
    ui->errorDescription->setPalette(palette2);

    ui->outputWord->clear();
    ui->outputWidget->close();
}
void RunWidget::onCloseClicked()
{
    this->close();
}
