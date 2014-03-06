#include "RunWidget.h"
#include "ui_RunWidget.h"

RunWidget::RunWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunWidget)
{
    ui->setupUi(this);
    ui->outputWord->clear();

    runStepsMade(101);
}

RunWidget::~RunWidget()
{
    delete ui;
}
void RunWidget::runStarted(QString input_word)
{
    ui->inputWidget->setWord(input_word);
    ui->outputWord->clear();
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

    //add new widget

}

void RunWidget::runFailed(QString input_word,
               RunError error,
               int steps_made)
{
    ui->inputWidget->setWord(input_word);
    ui->outputWord->setText("Error:");
    ui->stepsNumber->setText(QString::number(steps_made));

    QLabel* i_label;
    i_label->setText(error.getFullErrorInfo());

    ui->gridLayout->addWidget(i_label);
}
