#include "MarkovWordWidget.h"
#include "ui_MarkovWordWidget.h"

MarkovWordWidget::MarkovWordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkovWordWidget)
{
    ui->setupUi(this);
}

MarkovWordWidget::~MarkovWordWidget()
{
    delete ui;
}
