#ifndef TERMWIDGET_H
#define TERMWIDGET_H

#include <QWidget>
#include "Logic/FunctionsStorage.h"
#include "FunctionsListModel.h"

namespace Ui {
class TermWidget;
}

class TermWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TermWidget(QWidget *parent = 0);
    //void init(QString function_name="");
    ~TermWidget();
    
    void setFunctionPtr(const FunctionPtr function);
    void setName(const QString name);
    void setTerm(TermPtr term);

    void buildFunctionsList();
private:
    TermPtr _term;
    FunctionPtr _function_ptr;

    FunctionsListModel* _model;

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
    /**
     * @brief getParameterName
     * @param function_id
     * @param param_id
     * @return QString
     * get parameter name of function
     */
    const QString getParameterName(int function_id, int param_id);
    /**
     * @brief rebildChildWidgets
     * if again we click to ComboBox
     * we must delete all Son Widgets and Show new Widgets
     */
    void rebildChildWidgets();
signals:

public slots:

    void onChooseImplClick(int);
};

#endif // TERMWIDGET_H
