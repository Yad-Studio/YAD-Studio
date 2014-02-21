#include "Term.h"
#include <cassert>

TermPtr Term::create(const Type type)
{
    return std::shared_ptr<Term>(new Term(type));
}


void Term::setFunctionID(const FunctionID& id)
{
    assert(_type == Type::Function);
    _function_id = id;
    emit functionIDChanged(id);
}


void Term::setTermList(const TermPtrList& list)
{
    assert(_type == Type::Function);
    _terms_list = list;
    emit termListChanged(list);
}


void Term::setVariableIndex(const VariableIndex index)
{
    assert(_type == Type::Variable);
    _variable_index = index;
    emit variableIndexChanged(index);
}


const Term::Type Term::getType() const
{
    return _type;
}


const FunctionID Term::getFunctionID() const
{
    assert(_type == Type::Function);
    return _function_id;
}


const TermPtrList& Term::getTermList() const
{
    assert(_type == Type::Function);
    return _terms_list;
}


const VariableIndex Term::getVariableIndex() const
{
    assert(_type == Type::Variable);
    return _variable_index;
}

Term::Term(const Type type)
    : _type(type)
{
}
