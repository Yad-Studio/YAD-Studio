#include "LeftMenuWidget.h"
#include "ui_LeftMenuWidget.h"

LeftMenuWidget::LeftMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftMenuWidget)
{
    ui->setupUi(this);
}

LeftMenuWidget::~LeftMenuWidget()
{
    delete ui;
}
