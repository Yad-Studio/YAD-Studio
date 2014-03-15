#include "HistoryWidget.h"
#include "ui_HistoryWidget.h"
#include <QStringListModel>
#include <QListView>
#include <QStyledItemDelegate>
#include <QAbstractTextDocumentLayout>

#include "QMenu"

class HtmlDelegate : public QStyledItemDelegate
{
protected:
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

void HtmlDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 optionV4 = option;
    initStyleOption(&optionV4, index);

    QStyle *style = optionV4.widget? optionV4.widget->style() : QApplication::style();

    QTextDocument doc;
    doc.setHtml(optionV4.text);

    /// Painting item without text
    optionV4.text = QString();
    style->drawControl(QStyle::CE_ItemViewItem, &optionV4, painter);

    QAbstractTextDocumentLayout::PaintContext ctx;

    // Highlighting text if item is selected
    if (optionV4.state & QStyle::State_Selected)
        ctx.palette.setColor(QPalette::Text, optionV4.palette.color(QPalette::Active, QPalette::HighlightedText));

    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &optionV4);
    painter->save();
    painter->translate(textRect.topLeft());
    painter->setClipRect(textRect.translated(-textRect.topLeft()));
    doc.documentLayout()->draw(painter, ctx);
    painter->restore();
}

QSize HtmlDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 optionV4 = option;
    initStyleOption(&optionV4, index);

    QTextDocument doc;
    doc.setHtml(optionV4.text);
    doc.setTextWidth(optionV4.rect.width());
    return QSize(doc.idealWidth(), doc.size().height());
}


HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);

    QVector<QString> vec;
    //vec.push_back("test1");
    //vec.push_back("test2");
    historyChanged(vec);

    //make do not editable listView
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->listView->setItemDelegate(new HtmlDelegate);
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
       QStringList slist = getSelectedItems();

       //signal that we would like to delete world from the history
       if(!slist.empty())
           emit removeFromHistory(slist[0]);

    }
}
void HistoryWidget::doubleClick(QModelIndex index)
{
    QStringList slist = getSelectedItems();

    if(slist.size() > 0)
    {
        //put the world in input line
        emit inputWordSelected(slist[0]);
    }
}

QStringList HistoryWidget::getSelectedItems()
{
    QModelIndexList model_list = ui->listView->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, model_list)
    {
        int i = index.row();
        if(i < _history.size())
        {
            slist.append(_history[i]);
        }
    }

    return slist;
}

void HistoryWidget::deleteHistoryItem()
{
    //if there was an item selected - delete this item
    QStringList slist = getSelectedItems();

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
    _history = list;
    for(int i=0; i<list.size(); ++i)
    {
        QString w_len = QString("<span style='font-size:10px; color:#777777'>[%1] </span>").arg(list[i].size());
        QString text = QString("<span style='font-size:16px'>%1</span>").arg(list[i]);
        stringList->append(w_len+text);
    }

    QStringListModel* listModel = new QStringListModel(*stringList, NULL);
    ui->listView->setModel(listModel);
}
