#include "HistoryWidget.h"
#include "ui_HistoryWidget.h"

HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}
