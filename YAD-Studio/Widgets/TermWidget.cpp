#include "TermWidget.h"
#include "ui_TermWidget.h"

TermWidget::TermWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TermWidget)
{
    ui->setupUi(this);
}

TermWidget::~TermWidget()
{
    delete ui;
}
