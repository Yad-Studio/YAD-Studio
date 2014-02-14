#include "GUIEditWidget.h"
#include "ui_GUIEditWidget.h"

GUIEditWidget::GUIEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUIEditWidget)
{
    ui->setupUi(this);
}

GUIEditWidget::~GUIEditWidget()
{
    delete ui;
}
