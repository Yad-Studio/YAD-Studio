#ifndef LEFTMENUFUNCTIONITEMWIDGET_H
#define LEFTMENUFUNCTIONITEMWIDGET_H

#include <QWidget>

namespace Ui {
class LeftMenuFunctionItemWidget;
}

class LeftMenuFunctionItemWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LeftMenuFunctionItemWidget(QWidget *parent = 0);
    ~LeftMenuFunctionItemWidget();
    
private:
    Ui::LeftMenuFunctionItemWidget *ui;
};

#endif // LEFTMENUFUNCTIONITEMWIDGET_H
