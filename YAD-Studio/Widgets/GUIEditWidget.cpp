#include "GUIEditWidget.h"
#include "ui_GUIEditWidget.h"

GUIEditWidget::GUIEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUIEditWidget)
{
    ui->setupUi(this);
    ui->widget->init(getFunctionName());
}

GUIEditWidget::~GUIEditWidget()
{
    delete ui;
}
const QString GUIEditWidget::getFunctionName()
{
    return "MyFunction";
}
