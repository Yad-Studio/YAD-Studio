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

    /**
     * @brief getFunctionName
     * @return QString
     * get from Functioninfo the Function name
     */
    const QString getFunctionName();
};

#endif // GUIEDITWIDGET_H
