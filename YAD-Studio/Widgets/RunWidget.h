#ifndef RUNWIDGET_H
#define RUNWIDGET_H

#include <QWidget>

namespace Ui {
class RunWidget;
}

class RunWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RunWidget(QWidget *parent = 0);
    ~RunWidget();
    
private:
    Ui::RunWidget *ui;
};

#endif // RUNWIDGET_H
