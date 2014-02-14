#include "WorkingPanel.h"
#include "ui_WorkingPanel.h"

WorkingPanel::WorkingPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkingPanel)
{
    ui->setupUi(this);
}

WorkingPanel::~WorkingPanel()
{
    delete ui;
}
