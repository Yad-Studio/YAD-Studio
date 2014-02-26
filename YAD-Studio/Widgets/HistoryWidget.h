#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>

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
};

#endif // HISTORYWIDGET_H
