#include "Term.h"
#include <cassert>
#include "FunctionsStorage.h"
TermPtr Term::create(const Type type)
{
    return std::shared_ptr<Term>(new Term(type));
}


void Term::setFunctionID(const FunctionID& id)
{
    assert(_type == Type::Function);
    if(_function_id != id)
    {
        _function_id = id;

        FunctionPtr function = FunctionsStorage::getInstance()->getFunction(id);
        assert(function);


        unsigned int arguments = function->getArgumentsNumber();
        this->disconnect(this, SLOT(argumentsNumberChanged(uint)));

        Function* func_ptr = &*function;
        this->connect(func_ptr, SIGNAL(argumentsNumberChanged(uint)),
                      this, SLOT(argumentsNumberChanged(uint)));

        argumentsNumberChanged(arguments);
        emit functionIDChanged(id);
    }
}

void Term::argumentsNumberChanged(const unsigned int n)
{
    int number = n;
    if(_term_number != number)
    {
        _term_number = number;

        if(_terms_list.size() < number)
        {

            while(_terms_list.size() < number)
            {
                _terms_list.push_back(Term::create(Term::Type::Zero));
            }
        }
        emit termsNumberChanged(_term_number);
    }
}

void Term::setTerm(const ArgumentID id, const TermPtr& term)
{
    assert(_type == Type::Function);
    assert(id < _term_number);

    _terms_list[id] = term;
    emit termChanged(id, term);
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

const unsigned int Term::getTermsNumber() const
{
    assert(_type == Type::Function);
    return _term_number;
}

const FunctionID Term::getFunctionID() const
{
    assert(_type == Type::Function);
    return _function_id;
}


const VariableIndex Term::getVariableIndex() const
{
    assert(_type == Type::Variable);
    return _variable_index;
}

Term::Term(const Type type)
    : _type(type),
      _term_number(0)
{
}
