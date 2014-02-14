#include "FunctionInfoWidget.h"
#include "ui_FunctionInfoWidget.h"

FunctionInfoWidget::FunctionInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionInfoWidget)
{
    ui->setupUi(this);
}

FunctionInfoWidget::~FunctionInfoWidget()
{
    delete ui;
}
