#ifndef TERMWIDGET_H
#define TERMWIDGET_H

#include <QWidget>

namespace Ui {
class TermWidget;
}

class TermWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TermWidget(QWidget *parent = 0);
    ~TermWidget();
    
private:
    Ui::TermWidget *ui;
signals:

public slots:

    void onChooseImplClick(int);
};

#endif // TERMWIDGET_H
