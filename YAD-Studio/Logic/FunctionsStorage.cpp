#include "FunctionsStorage.h"
#include <cassert>
FunctionsStorage::FunctionsStorage()
{
}

FunctionsStorage* FunctionsStorage::getInstance()
{
    return &_instance;
}

FunctionsStorage FunctionsStorage::_instance;

FunctionID FunctionsStorage::st_next_id = 1;

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

        _function_storage[function->getID()] = function;
    }
}
