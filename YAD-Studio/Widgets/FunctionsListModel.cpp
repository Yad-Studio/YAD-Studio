#include "FunctionsListModel.h"
#include <QBrush>
#include <QFont>
FunctionsListModel::FunctionsListModel(FunctionPtr parent_function,
                                       QObject *parent) :
    QAbstractListModel(parent),
    _parent_function(parent_function)
{
    for(unsigned int i=0; i<_parent_function->getArgumentsNumber(); ++i)
    {
        TermPtr term = Term::create(Term::Type::Variable);
        term->setVariableIndex(i);
        _variables.push_back(term);
    }

    _system_functions = FunctionsStorage::getInstance()->getSystemTerms();

    const QVector<FunctionID> functions = FunctionsStorage::getInstance()->getAllUserFunctions();
    for(FunctionID i: functions)
    {
        TermPtr term = Term::create(Term::Type::Function);
        term->setFunctionID(i);
        _functions.push_back(term);
    }
}
QVariant FunctionsListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        TermPtr term = getTerm(index.row());
        return termToString(term);
    }

    //    if(role == Qt::DecorationRole)
    //    {
    //        int row = index.row();
    //        QColor color = colors.value(row);

    //        QPixmap pixmap(26, 26);
    //        pixmap.fill(color);

    //        QIcon icon(pixmap);

    //        return icon;
    //    }

    if(role == Qt::EditRole)
    {
        TermPtr term = getTerm(index.row());
        return termToString(term);
    }

    if(role == Qt::ToolTipRole)
    {
        return "function comment";
    }

    if (role == Qt::BackgroundRole)
    {
        QColor function_color(216, 234, 254);
        QColor system_color(253, 254, 216);
        QColor variable_color(225, 254, 216);

        TermPtr term = getTerm(index.row());
        if(term->getType() == Term::Type::Function)
        {
            if(term->getFunctionID() != FunctionsStorage::S)
                return QBrush(function_color);
            else
                return QBrush(system_color);
        }
        else if(term->getType() == Term::Type::Variable)
        {
            return QBrush(variable_color);
        }
        return QBrush(system_color);
    }

    if (role == Qt::FontRole)
    {

        QFont boldFont;
        boldFont.setBold(true);

        TermPtr term = getTerm(index.row());
        if(term->getType() == Term::Type::Variable)
            return boldFont;
    }

//    if (role ==  Qt::TextAlignmentRole)
//    {
//        return Qt::AlignCenter;
//    }
    return QVariant();
}

int FunctionsListModel::rowCount(const QModelIndex &parent) const
{
    return (_variables.size() +_system_functions.size() +_functions.size());
}
//bool FunctionsListModel::insertRows(int position, int rows,
//                const QModelIndex &parent = QModelIndex());
//bool FunctionsListModel::removeRows(int position, int rows,
//                const QModelIndex &parent = QModelIndex());

//QModelIndex FunctionsListModel::getTermIndex(TermPtr term);

TermPtr FunctionsListModel::getTerm(const int index) const
{
    int i = index;
    if(i<_variables.size())
        return _variables[i];

    i -= _variables.size();
    if(i<_system_functions.size())
        return _system_functions[i];

    i-=_system_functions.size();

    if(i<_functions.size())
        return _functions[i];

    return nullptr;
}


QString FunctionsListModel::termToString(TermPtr term) const
{
    if(term->getType() == Term::Type::Variable)
    {
        return _parent_function->getArgumentName(term->getVariableIndex());
    }
    else if(term->getType() == Term::Type::Zero)
    {
        return "0";
    }
    else if(term->getType() == Term::Type::Variable_Min)
    {
        return "*";
    }
    else
    {
        FunctionPtr funptr = FunctionsStorage::getInstance()->getFunction(term->getFunctionID());

        QString function = funptr->getName();
        function += "(";
        for(unsigned int i=0; i<funptr->getArgumentsNumber(); ++i)
        {
            if(i)
                function += ", ";
            function += funptr->getArgumentName(i);
        }
        function += ")";
        return function;
    }
    //Error mode
    return "";
}
