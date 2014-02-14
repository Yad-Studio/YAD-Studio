#include "MyModule.h"

MyModule::MyModule(QObject *parent) :
    QObject(parent)
{
}

void MyModule::onAction()
{
    emit mySignal(5, "Hello");
}
