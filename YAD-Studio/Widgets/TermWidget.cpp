#include "TermWidget.h"
#include "ui_TermWidget.h"
#include "FunctionsListModel.h"
TermWidget::TermWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TermWidget),
    _model(nullptr)
{
    ui->setupUi(this);

    //TODO: get function list
    //two param function
    //    addFunction("add(x,y)");
    //    //trhee param function
    //    addFunction("multiply(x,y,z)");
    //    //veriable
    //    addFunction("y");

    connect(ui->function_impl,
            SIGNAL(activated(int)),
            this,
            SLOT(onChooseImplClick(int)));

}
void TermWidget::buildFunctionsList()
{
    _model = new FunctionsListModel(_function_ptr,
                                    this);
    ui->function_impl->setModel(_model);
}

void TermWidget::setFunctionPtr(const FunctionPtr function)
{
    _function_ptr = function;
}

void TermWidget::setName(const QString name)
{
    ui->function_name->setText(name + " = ");
}

void TermWidget::setTerm(TermPtr term)
{
    _term = term;
}

//void TermWidget::init(QString function_name)
//{
//    if(function_name.size()>0)
//        ui->function_name->setText(function_name);
//}

TermWidget::~TermWidget()
{
    delete ui;
}

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void TermWidget::onChooseImplClick(int)
{
    //TODO: delete previous child widgets, if there are
    //rebildChildWidgets();

    //get index of curr choosen ComboBox
    int index = ui->function_impl->currentIndex();

    if(_model)
    {
        TermPtr term = _model->getTerm(index);
        if(term)
        {
            _term->setType(term->getType());

            //Delete old widgets
            clearLayout(ui->grid_4, true);

            if(term->getType() == Term::Type::Function)
            {
                FunctionPtr function = FunctionsStorage::getInstance()->getFunction(term->getFunctionID());

                //TODO: get how many params has this function
                //and add so many TermWidgets
                int param_num = function->getArgumentsNumber();
                _term->setFunctionID(function->getID());



                for(int i=0; i<param_num; ++i)
                {
                    QString param_name = function->getArgumentName(i);
                    TermWidget *term_widget = new TermWidget(this);

                    term_widget->setFunctionPtr(_function_ptr);
                    term_widget->setName(param_name);
                    term_widget->setTerm(_term->getTerm(i));
                    term_widget->buildFunctionsList();

                    //term_widget->init(param_name);

                    ui->grid_4->addWidget(term_widget);
                }
            }
            else if(term->getType() == Term::Type::Variable)
            {
                _term->setVariableIndex(term->getVariableIndex());
            }

            ui->gridLayout_5->update();
        }
    }
    //TODO: find in "function params" list - is it a function or a variable

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
void TermWidget::rebildChildWidgets()
{
    //if (!ui->grid_4->children().isEmpty())
    //{
    //ui->grid_4->children().toStdList().clear();


    for (int i = 0; i <  ui->grid_4->count(); ++i)
    {
        ui->grid_4->itemAt(i)->widget()->setVisible(false);
    }

    //}
}
