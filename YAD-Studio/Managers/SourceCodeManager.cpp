#include "SourceCodeManager.h"

SourceCodeManager* SourceCodeManager::_instance = nullptr;
SourceCodeManager::SourceCodeManager():
    _source_code("")
{
}
SourceCodeManager* SourceCodeManager::getInstance( )
{
      if (_instance == nullptr)
        _instance = new SourceCodeManager();
     return _instance;
}
QString SourceCodeManager::getSourceCode()
{
    return _source_code;
}
void SourceCodeManager::setSourceCode(QString new_source)
{
    _source_code = new_source;
    emit sourceCodeChanged(new_source);
}
void SourceCodeManager::setNewSourceCodeFromFile(QString new_source)
{
    _source_code = new_source;
    emit newSourceCodeWasLoaded(new_source);
}
