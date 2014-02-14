#ifndef LEFTMENUWIDGET_H
#define LEFTMENUWIDGET_H

#include <QWidget>

namespace Ui {
class LeftMenuWidget;
}

class LeftMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LeftMenuWidget(QWidget *parent = 0);
    ~LeftMenuWidget();

private:
    Ui::LeftMenuWidget *ui;
};

#endif // LEFTMENUWIDGET_H
