#ifndef GUIEDITWIDGET_H
#define GUIEDITWIDGET_H
#include "Logic/FunctionsStorage.h"
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

public slots:
    void onFunctionActive(FunctionPtr function);
private:
    Ui::GUIEditWidget *ui;

    /**
     * @brief getFunctionName
     * @return QString
     * get from Functioninfo the Function name
     */
    const QString getFunctionName();

    FunctionPtr _active_function;

};

#endif // GUIEDITWIDGET_H
