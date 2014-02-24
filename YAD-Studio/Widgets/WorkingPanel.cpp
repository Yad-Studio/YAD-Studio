#include "WorkingPanel.h"
#include "ui_WorkingPanel.h"
#include "GUIEditWidget.h"
WorkingPanel::WorkingPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkingPanel)
{
    ui->setupUi(this);
}

void WorkingPanel::onFunctionActive(FunctionPtr function)
{
    ui->guiEditWidget->onFunctionActive(function);
}

WorkingPanel::~WorkingPanel()
{
    delete ui;
}
