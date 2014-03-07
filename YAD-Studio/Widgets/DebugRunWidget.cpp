#include "DebugRunWidget.h"
#include "ui_DebugRunWidget.h"


DebugRunWidget::DebugRunWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugRunWidget)
{
    ui->setupUi(this);

    if(!isVisible())
        setVisible(true);

    debugStarted("");


    connect(ui->closeButton,
            SIGNAL(clicked()),
            this,
            SLOT(onCloseButtonClicked()));

    connect(ui->nextButton,
            SIGNAL(clicked()),
            this,
            SLOT(onNextButtonClicked()));

    connect(ui->stopButton,
            SIGNAL(clicked()),
            this,
            SLOT(onStopButtonCliked()));

    connect(ui->continueButton,
            SIGNAL(clicked()),
            this,
            SLOT(onContinueButtonClicked()));

    debugStepFinished(3,"aaab","bab",MarkovRule("aa","b"));
}

DebugRunWidget::~DebugRunWidget()
{
    delete ui;
}
void DebugRunWidget::debugStarted(QString input_word)
{
    if(!isVisible())
        setVisible(true);

    ui->inputWidget->setWord(input_word);

    ui->output->setVisible(false);
    ui->outputWidget->setVisible(false);

    ui->error->setVisible(false);
    ui->errorDescription->setVisible(false);

    ui->rule->setVisible(false);
    ui->ruleText->setVisible(false);

    ui->steps->setVisible(false);
    ui->stepsNumber->setVisible(false);

    ui->stopButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->nextButton->setVisible(false);
}

void DebugRunWidget::debugSuccess(QString input_word,
             QString output_word,
             int steps_made)
{
    ui->title->setTitle(tr("Debug Finished"));
    ui->inputWidget->setWord(input_word);

    ui->output->setVisible(true);

    ui->outputWidget->setVisible(true);
    ui->outputWidget->setWord(output_word);

    ui->error->setVisible(false);
    ui->errorDescription->setVisible(false);

    ui->rule->setVisible(false);
    ui->ruleText->setVisible(false);


    ui->steps->setVisible(true);
    ui->stepsNumber->setVisible(true);
    ui->stepsNumber->setText(QString::number(steps_made));

    ui->stopButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->nextButton->setVisible(false);
}

void DebugRunWidget::debugFailed(QString input_word,
            RunError error,
            int steps_made)
{
    ui->inputWidget->setWord(input_word);

    ui->error->setVisible(true);
    ui->errorDescription->setVisible(true);

    ui->rule->setVisible(false);
    ui->ruleText->setVisible(false);

    ui->output->setVisible(false);
    ui->outputWidget->setVisible(false);

    ui->steps->setVisible(true);
    ui->stepsNumber->setVisible(true);
    ui->stepsNumber->setText(QString::number(steps_made));

    ui->errorDescription->setText(error.getFullErrorInfo());

    QPalette palette = ui->error->palette();
    palette.setColor(ui->error->foregroundRole(), Qt::red);
    ui->error->setPalette(palette);

    QPalette palette2 = ui->errorDescription->palette();
    palette2.setColor(ui->errorDescription->foregroundRole(), Qt::red);
    ui->errorDescription->setPalette(palette2);

    ui->stopButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->nextButton->setVisible(false);
}

void DebugRunWidget::debugStepFinished(int step_number,
                  QString before_rule_applied,
                  QString after_rule_applied,
                  MarkovRule applied_rule)
{
    ui->inputWidget->setWord(before_rule_applied);

    ui->error->setVisible(false);
    ui->errorDescription->setVisible(false);

    ui->output->setVisible(true);
    ui->outputWidget->setVisible(true);
    ui->inputWidget->setWord(after_rule_applied);

    ui->steps->setVisible(true);
    ui->stepsNumber->setVisible(true);
    ui->stepsNumber->setText(QString::number(step_number));

    ui->stopButton->setVisible(false);
    ui->continueButton->setVisible(false);
    ui->nextButton->setVisible(false);

    ui->rule->setVisible(true);
    ui->ruleText->setVisible(true);

    ui->ruleText->setText(tr("%1 -> %2").arg(applied_rule.getLeftPart()).arg(applied_rule.getRightPart()));

    //ad info to Debug Log
//    Step #{number_of_step}
//    Before: {word_before_rule_applied}
//    Rule: {rule}
//    After: {word_after_rule_applied}
    // <font color='red'>Some text</font>
    ui->debugLog->setText(tr("Step #%1<br> <#ff0000> Before : %2<br>Rule: %3<br>After: %4<br>").arg(QString::number(step_number)).arg(before_rule_applied).arg(applied_rule.getFullRule()).arg(after_rule_applied));
}

void DebugRunWidget::breakPointReached(int line_number)
{
    //it is enought - because previously the debugStepFinished was called
    ui->stopButton->setVisible(true);
    ui->continueButton->setVisible(true);
    ui->nextButton->setVisible(true);

    emit showBreakPoint(line_number);
}
void DebugRunWidget::onContinueButtonClicked()
{
    emit continueClicked();
    emit removeBreakPoint();
}

void DebugRunWidget::onNextButtonClicked()
{
    emit nextStepClicked();
    emit removeBreakPoint();
}

void DebugRunWidget::onStopButtonCliked()
{
    emit stopClicked();
    emit removeBreakPoint();
}

void DebugRunWidget::onCloseButtonClicked()
{
    setVisible(false);
}
