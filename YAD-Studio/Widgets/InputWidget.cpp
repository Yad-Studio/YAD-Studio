#include "InputWidget.h"
#include "ui_InputWidget.h"
#include "QPushButton"

InputWidget::InputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputWidget)
{
    ui->setupUi(this);

    _can_run_algorythm = true;

    //run button clicked
    connect(ui->runButton,
            SIGNAL(clicked()),
            this,
            SLOT(runCliked()));

    //run with debug cliked
    connect(ui->runWithDebug,
            SIGNAL(clicked()),
            this,
            SLOT(runWithDebugClicked()));

    //save clicked
    connect(ui->runStepByStep,
            SIGNAL(clicked()),
            this,
            SLOT(runWithDebugStepByStepClicked()));
}

InputWidget::~InputWidget()
{
    delete ui;
}
void InputWidget::runStarted()
{
    ui->runButton->setEnabled(false);
    ui->runWithDebug->setEnabled(false);
    ui->runStepByStep->setEnabled(false);
}

void InputWidget::runFinished()
{
    if(_can_run_algorythm)
    {
        ui->runButton->setEnabled(true);
        ui->runWithDebug->setEnabled(true);
        ui->runStepByStep->setEnabled(true);
    }
    else
    {
        ui->runButton->setEnabled(false);
        ui->runWithDebug->setEnabled(false);
        ui->runStepByStep->setEnabled(false);
    }
}

void InputWidget::setInput(QString new_input_word)
{
    ui->lineEdit->setText(new_input_word);
}

void InputWidget::canRunAlgorithm(bool can_run)
{
    _can_run_algorythm = can_run;

    if(!_can_run_algorythm)
    {
        ui->runButton->setEnabled(false);
        ui->runWithDebug->setEnabled(false);
        ui->runStepByStep->setEnabled(false);
    }
    else
    {
        ui->runButton->setEnabled(true);
        ui->runWithDebug->setEnabled(true);
        ui->runStepByStep->setEnabled(true);
    }
}
void InputWidget::runCliked( )
{
    emit run(ui->lineEdit->text());
    emit addToHistory(ui->lineEdit->text());
}
void InputWidget::runWithDebugClicked()
{
    emit runWithDebug(ui->lineEdit->text());
    emit addToHistory(ui->lineEdit->text());
}
void InputWidget::runWithDebugStepByStepClicked()
{
    emit runWithDebugStepByStep(ui->lineEdit->text());
    emit addToHistory(ui->lineEdit->text());
}

void InputWidget::saveCliked()
{
    emit save();
}
