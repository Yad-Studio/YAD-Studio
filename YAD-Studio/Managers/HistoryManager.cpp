#include "HistoryManager.h"

HistoryManager* HistoryManager::_instance = nullptr;

HistoryManager::HistoryManager()
{
}
HistoryManager* HistoryManager::getInstance( )
{
      if (_instance == nullptr)
        _instance = new HistoryManager();
     return _instance;
}
QVector<QString> HistoryManager::getHistory()
{
    return _history;
}

void HistoryManager::addToHistory(QString input_word)
{
    if(input_word.size() && !_history.contains(input_word))
        _history.push_back(input_word);

    emit historyChanged(_history);
}

void HistoryManager::removeFromHistory(QString input_word)
{
    int i = _history.indexOf(input_word);
    if( i != -1)
        _history.remove(i);

    emit historyChanged(_history);
}

void HistoryManager::clearHistory()
{
    _history.clear();

    emit historyChanged(_history);
}

void HistoryManager::addToHistory(QVector<QString> words)
{
    for(int i=0; i<words.size(); ++i)
    {
        if(!_history.contains(words[i]))
            _history.push_back(words[i]);
    }

    emit historyChanged(_history);
}
