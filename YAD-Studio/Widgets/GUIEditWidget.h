#ifndef GUIEDITWIDGET_H
#define GUIEDITWIDGET_H

#include <QWidget>

namespace Ui {
class GUIEditWidget;
}

class GUIEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GUIEditWidget(QWidget *parent = 0);
    ~GUIEditWidget();

private:
    Ui::GUIEditWidget *ui;
};

#endif // GUIEDITWIDGET_H
