#ifndef MARKOVWORDWIDGET_H
#define MARKOVWORDWIDGET_H

#include <QWidget>

namespace Ui {
class MarkovWordWidget;
}

class MarkovWordWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MarkovWordWidget(QWidget *parent = 0);
    ~MarkovWordWidget();
    
private:
    Ui::MarkovWordWidget *ui;
};

#endif // MARKOVWORDWIDGET_H
