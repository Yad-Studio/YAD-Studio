#include "TermWidget.h"
#include "ui_TermWidget.h"

TermWidget::TermWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TermWidget)
{
    ui->setupUi(this);

    //TODO: get function list
    //two param function
    addFunction("add(x,y)");
    //trhee param function
    addFunction("multiply(x,y,z)");
    //veriable
    addFunction("y");

    connect(ui->function_impl,
            SIGNAL(activated(int)),
            this,
            SLOT(onChooseImplClick(int)));

    init();
}
void TermWidget::init(QString function_name)
{
    if(function_name.size()>0)
        ui->function_name->setText(function_name);
}

TermWidget::~TermWidget()
{
    delete ui;
}
void TermWidget::onChooseImplClick(int)
{
    //get index of curr choosen ComboBox
    int index = ui->function_impl->currentIndex();

    //TODO: find in "function params" list - is it a function or a variable
    if(isFunction(index))
    {
        //TODO: get how many params has this function
        //and add so many TermWidgets
        int param_num = getParamNumber(index);

        for(unsigned int i=0; i<param_num; ++i)
        {
            QString param_name = getParameterName(index,
                                                  i);
            TermWidget *term_widget = new TermWidget(this);
            term_widget->init(param_name);

            ui->grid_4->addWidget(term_widget);

        }

    }


}
void TermWidget::addFunction(QString name)
{
    ui->function_impl->addItem(name);
}
bool TermWidget::isFunction(int id_in_list)
{
    if (id_in_list==0 || id_in_list == 1)
        return true;
    return false;
}
int TermWidget::getParamNumber(int id_in_list)
{
    int result = 2;
    if(id_in_list == 1)
        result  = 3;
    return result;
}
const QString TermWidget::getParameterName(int function_id,
                                           int param_id)
{
    QString result = "P";
    if ( function_id == 0)
    {
        if (param_id == 0)
            result = "x";
        else
            result = "y";
    }
    else if ( function_id == 1)
    {
        if (param_id == 0)
            result = "x";
        else if (param_id == 1)
            result = "y";
        else
            result = "z";
    }
    return result;
}
