#include "TheoryEditWidget.h"
#include "ui_TheoryEditWidget.h"

TheoryEditWidget::TheoryEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TheoryEditWidget)
{
    ui->setupUi(this);
}

TheoryEditWidget::~TheoryEditWidget()
{
    delete ui;
}
