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
    /**
     * @brief addFunction
     * @param name
     * simulate function list in ComboBox
     */
    void addFunction(QString name);
    /**
     * @brief isFunction
     * @param id_in_list
     * @return bool
     * is list[i]of ComboBox - a function or a variable
     */
    bool isFunction(int id_in_list);
    /**
     * @brief getParamNumber
     * @param id_in_list
     * @return parameter quantity
     * get how many parameters has the function with id = id_in_list
     */
    int getParamNumber(int id_in_list);
signals:

public slots:

    void onChooseImplClick(int);
};

#endif // TERMWIDGET_H
