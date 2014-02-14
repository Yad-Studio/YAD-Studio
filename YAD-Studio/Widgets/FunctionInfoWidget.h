#ifndef FUNCTIONINFOWIDGET_H
#define FUNCTIONINFOWIDGET_H

#include <QWidget>

namespace Ui {
class FunctionInfoWidget;
}

class FunctionInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionInfoWidget(QWidget *parent = 0);
    ~FunctionInfoWidget();

private:
    Ui::FunctionInfoWidget *ui;
};

#endif // FUNCTIONINFOWIDGET_H
