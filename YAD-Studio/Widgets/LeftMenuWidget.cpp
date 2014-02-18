#include "LeftMenuWidget.h"
#include "ui_LeftMenuWidget.h"
#include <QStandardItemModel>
#include <QStringListModel>

LeftMenuWidget::LeftMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftMenuWidget)
{
    QStringList string_list;
    string_list.append("abc");
    string_list.append("123");
    QStringListModel* model = new QStringListModel(this);

    ui->setupUi(this);
    ui->listView->setModel(model);
    model->insertRows(model->rowCount(),1);
    //QModelIndex index = model->index(model->rowCount()-1);
    model->setData(model->index(model->rowCount()-1),"hello");
}

LeftMenuWidget::~LeftMenuWidget()
{
    delete ui;
}
