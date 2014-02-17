#include "FunctionsStorage.h"

FunctionsStorage::FunctionsStorage()
{
}

FunctionsStorage* FunctionsStorage::getInstance()
{
    return &_instance;
}

FunctionsStorage FunctionsStorage::_instance;
