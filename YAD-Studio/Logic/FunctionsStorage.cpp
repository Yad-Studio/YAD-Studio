#include "FunctionsStorage.h"
#include <cassert>
FunctionsStorage::FunctionsStorage()
{
    FunctionPtr s = Function::create();
    s->setFunctionName("S");
    s->setArgumentsNumber(1);
    s->setArgumentName(0, "_x");
    s->setComment(QObject::tr("S(_x) = _x + 1"));
    s->setID(S);

    QObject::connect(&_mapper, SIGNAL(mapped(int)),
            this, SIGNAL(onFunctionChanged(int)));

    this->addFunction(s);

    TermPtr s_term = Term::create(Term::Type::Function);
    s_term->setFunctionID(S);

    _system_terms.push_back(s_term);
    _system_terms.push_back(Term::create(Term::Type::Zero));
    _system_terms.push_back(Term::create(Term::Type::Variable_Min));

}

const QVector<TermPtr>& FunctionsStorage::getSystemTerms()
{
    return _system_terms;
}
const QVector<FunctionID> FunctionsStorage::getAllUserFunctions()
{
    QVector<FunctionID> result;
    result.reserve(_function_storage.size()-1);

    for(auto i:_function_storage.keys())
    {
        if(i != S)
            result.push_back(i);
    }
    return result;
}

FunctionsStorage* FunctionsStorage::getInstance()
{
    static FunctionsStorage _instance;
    return &_instance;
}

//FunctionsStorage FunctionsStorage::_instance;

FunctionID FunctionsStorage::st_next_id = 100;

FunctionPtr FunctionsStorage::getFunction(const FunctionID id)
{
    auto it = _function_storage.find(id);
    if(it != _function_storage.end())
    {
        return it.value();
    }
    return FunctionPtr(nullptr);
}

void FunctionsStorage::addFunction(FunctionPtr function)
{
    if(function->getID() == 0)
    {
        //auto increment id
        function->setID(st_next_id);
        st_next_id++;
    }
    else
    {
        auto it = _function_storage.find(function->getID());

        //ID duplication
        assert(it == _function_storage.end());

        //Next autoincrement
        if(function->getID() >= st_next_id)
            st_next_id = function->getID() + 1;


    }


    Function* f = &*function;

    _mapper.setMapping(f, f->getID());

    connect(f, SIGNAL(argumentNameChanged(ArgumentID,ArgumentName)),
            &_mapper, SLOT(map()));
    connect(f, SIGNAL(argumentsNumberChanged(uint)),
            &_mapper, SLOT(map()));
    connect(f, SIGNAL(commentChanged(Comment)),
            &_mapper, SLOT(map()));
    connect(f, SIGNAL(functionNameChanged(FunctionName)),
            &_mapper, SLOT(map()));
    connect(f, SIGNAL(typeChanged(Function::Type)),
            &_mapper, SLOT(map()));

    _function_storage[function->getID()] = function;
}

FunctionID FunctionsStorage::S = 1;
