#include "HistoryWidget.h"
#include "ui_HistoryWidget.h"
#include <QStringListModel>

HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);

    QVector<QString> vec;
    vec.push_back("test1");
    vec.push_back("test2");
    historyChanged(vec);
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}
void HistoryWidget::historyChanged(QVector<QString> list)
{
    QStringList* stringList = new QStringList();

    for(int i=0; i<list.size(); ++i)
    {
        stringList->append(list[i]);
    }

    QStringListModel* listModel = new QStringListModel(*stringList, NULL);
    ui->listView->setModel(listModel);
}
