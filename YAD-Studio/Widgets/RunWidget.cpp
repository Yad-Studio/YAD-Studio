#include "RunWidget.h"
#include "ui_RunWidget.h"

RunWidget::RunWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunWidget)
{
    ui->setupUi(this);
}

RunWidget::~RunWidget()
{
    delete ui;
}
