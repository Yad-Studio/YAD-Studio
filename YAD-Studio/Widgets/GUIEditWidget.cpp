#include "GUIEditWidget.h"
#include "ui_GUIEditWidget.h"
#include "TermWidget.h"

GUIEditWidget::GUIEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUIEditWidget)
{
    ui->setupUi(this);

    ui->base->setVisible(false);
    ui->step->setVisible(false);
}
void GUIEditWidget::onFunctionActive(FunctionPtr function)
{
    ui->base->setVisible(false);
    ui->step->setVisible(false);

    if(function->getType() == Function::Type::Recursive)
    {
        QString name;
        name += function->getName();
        name += "(";
        for(unsigned int i=0; i<function->getArgumentsNumber(); ++i)
        {
            if(i)
                name += ", ";

            if(i+1 == function->getArgumentsNumber())
                name += "0";
            else
                name += function->getArgumentName(i);
        }
        name += ")";

        ui->base->setName(name);
        ui->base->setTerm(function->getRecursionBaseTerm());
        ui->base->setFunctionPtr(function);
        ui->base->setVisible(true);
        ui->base->buildFunctionsList();
    }

    QString name;
    name += function->getName();
    name += "(";
    for(unsigned int i=0; i<function->getArgumentsNumber(); ++i)
    {
        if(i)
            name += ", ";

        name += function->getArgumentName(i);
        if(i+1 == function->getArgumentsNumber())
            name += "+1";
    }
    name += ")";

    ui->step->setName(name);
    ui->step->setTerm(function->getMainTerm());
    ui->step->setFunctionPtr(function);
    ui->step->setVisible(true);
    ui->step->buildFunctionsList();
}

GUIEditWidget::~GUIEditWidget()
{
    delete ui;
}
const QString GUIEditWidget::getFunctionName()
{
    return "MyFunction";
}
