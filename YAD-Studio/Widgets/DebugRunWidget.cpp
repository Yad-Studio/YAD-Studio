#include "DebugRunWidget.h"
#include "ui_DebugRunWidget.h"

DebugRunWidget::DebugRunWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugRunWidget)
{
    ui->setupUi(this);
}

DebugRunWidget::~DebugRunWidget()
{
    delete ui;
}
