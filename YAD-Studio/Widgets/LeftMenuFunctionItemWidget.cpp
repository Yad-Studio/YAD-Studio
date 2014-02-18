#include "leftmenufunctionitemwidget.h"
#include "ui_leftmenufunctionitemwidget.h"

LeftMenuFunctionItemWidget::LeftMenuFunctionItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftMenuFunctionItemWidget)
{
    ui->setupUi(this);
}

LeftMenuFunctionItemWidget::~LeftMenuFunctionItemWidget()
{
    delete ui;
}
