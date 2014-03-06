#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include "QListWidgetItem"

namespace Ui {
class HistoryWidget;
}

class HistoryWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HistoryWidget(QWidget *parent = 0);
    ~HistoryWidget();
    
private:
    Ui::HistoryWidget *ui;



public slots:
    // the list in widget must be updated
    //(delete all previous history and write new QVector)
    void historyChanged(QVector<QString> list);

    void showContextMenu(const QPoint& pos);
    void doubleClick(QModelIndex index);
    void deleteHistoryItem();

signals:
    //signal is triggered when user double clicks the word in the list.
    //The parameter is the word which user clicked.
    void inputWordSelected(QString word);

    //signal should be emitted when user deletes the word from the list.
    //There is no need to delete word manually from the list
    //as historyChanged will be called automatically.
    void removeFromHistory(QString word);
};

#endif // HISTORYWIDGET_H
