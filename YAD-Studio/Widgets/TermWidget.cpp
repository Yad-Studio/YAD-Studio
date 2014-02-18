#include "TermWidget.h"
#include "ui_TermWidget.h"

TermWidget::TermWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TermWidget)
{
    ui->setupUi(this);

    onChooseImplClick(2);

    connect(ui->function_impl,
            SIGNAL(activated(int)),
            this,
            SLOT(onChooseImplClick(int)));
}

TermWidget::~TermWidget()
{
    delete ui;
}
void TermWidget::onChooseImplClick(int)
{
    ui->function_impl->addItem("Item1");
}
