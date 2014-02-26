#include "LineInfoWidget.h"
#include "ui_LineInfoWidget.h"

LineInfoWidget::LineInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineInfoWidget)
{
    ui->setupUi(this);
}

LineInfoWidget::~LineInfoWidget()
{
    delete ui;
}
