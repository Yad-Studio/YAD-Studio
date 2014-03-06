#include "HistoryWidget.h"
#include "ui_HistoryWidget.h"
#include <QStringListModel>
#include <QListView>
#include "QMenu"


HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);

    QVector<QString> vec;
    vec.push_back("test1");
    vec.push_back("test2");
    historyChanged(vec);

    //make do not editable listView
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //double click to select item
    connect(ui->listView,
            SIGNAL(doubleClicked(QModelIndex)),
            this,
            SLOT(doubleClick(QModelIndex)));


    //add contex menu
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showContextMenu(const QPoint&)));

    //another way to delete a history word '-' button
    connect (ui->toolButton,
             SIGNAL(clicked()),
             this,
             SLOT(deleteHistoryItem()));

}

void HistoryWidget::showContextMenu(const QPoint& pos)
{
    QPoint globalPos = this->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction(tr("Delete"));

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
       QModelIndexList list = ui->listView->selectionModel()->selectedIndexes();

       QStringList slist;
       foreach(const QModelIndex &index, list)
       {
           slist.append( index.data(Qt::DisplayRole ).toString());
       }

       //signal that we would like to delete world from the history
       emit removeFromHistory(slist[0]);
    }
}
void HistoryWidget::doubleClick(QModelIndex index)
{
    QModelIndexList model_list = ui->listView->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, model_list)
    {
        slist.append( index.data(Qt::DisplayRole ).toString());
    }

    //put the world in input line
    emit inputWordSelected(slist[0]);
}
void HistoryWidget::deleteHistoryItem()
{
    //if there was an item selected - delete this item
    QModelIndexList list = ui->listView->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, list)
    {
        slist.append( index.data(Qt::DisplayRole ).toString());
    }

    if(!slist.empty())
    {
        //signal that we would like to delete world from the history
        emit removeFromHistory(slist[0]);
    }
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
