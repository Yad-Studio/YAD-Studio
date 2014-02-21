#include "Function.h"
#include <cassert>

FunctionPtr Function::create()
{
    return std::shared_ptr<Function>(new Function);
}

void Function::setType(const Type type)
{
    _type = type;
    emit typeChanged(_type);
}

void Function::setID(const FunctionID id)
{
    _id = id;
    emit IDChanged(_id);
}

void Function::setFunctionName(const FunctionName& name)
{
    _name = name;
    emit functionNameChanged(_name);
}

void Function::setMainTerm(const TermPtr& term)
{
    _main_term = term;
    emit mainTermChanged(_main_term);
}

void Function::setArgumentsList(const Arguments& lst)
{
    _arguments_list = lst;
    emit argumentsListChanged(_arguments_list);
}

void Function::setRecursionBaseTerm(const TermPtr& term)
{
    assert(_type == Type::Recursive);
    _main_term = term;
    emit mainTermChanged(_main_term);
}

const unsigned int Function::getArgumentsNumber() const
{
    return _arguments_list.size();
}

void Function::setComment(const Comment& comment)
{
    _comment = comment;
    emit commentChanged(_comment);
}

const Function::Type Function::getType() const
{
    return _type;
}
const FunctionID Function::getID() const
{
    return _id;
}
const FunctionName& Function::getName() const
{
    return _name;
}
const TermPtr& Function::getMainTerm() const
{
    return _main_term;
}
const TermPtr& Function::getRecursionBaseTerm() const
{
    assert(_type == Type::Recursive);
    return _base_term;
}

Function::Function()
    : _type(Type::Normal),
      _id(-1),
      _name(),
      _main_term(nullptr),
      _arguments_list(),
      _base_term(nullptr),
      _comment()
{

}
