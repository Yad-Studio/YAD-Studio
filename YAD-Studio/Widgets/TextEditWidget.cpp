#include "TextEditWidget.h"
#include "ui_TextEditWidget.h"

TextEditWidget::TextEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEditWidget)
{
    ui->setupUi(this);
}

TextEditWidget::~TextEditWidget()
{
    delete ui;
}
