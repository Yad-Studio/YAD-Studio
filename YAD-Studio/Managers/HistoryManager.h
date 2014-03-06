#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H
#include "QVector"
#include "QString"
#include <QObject>

class HistoryManager: public QObject
{
    Q_OBJECT
public:
    static HistoryManager* getInstance( );

    //returns the latest history
    QVector<QString> getHistory();

public slots:
    //should be added to history if it is not yet in history
    void addToHistory(QString input_word);
    //  word should be removed from history
    void removeFromHistory(QString input_word);
    //all history should be erased
    void clearHistory();
    //same as first slot but with multiple words
    void addToHistory(QVector<QString> words);

signals:
    // emitted when the history was changed.
    void historyChanged(QVector<QString> new_words);

    //When word was selected
    void wordSelected(QString input_word);
private:
    //it is a singletone
    HistoryManager();

    HistoryManager(HistoryManager const&);              // don't Implement
    void operator=(HistoryManager const&); // don't implement


    static HistoryManager* _instance;
    QVector<QString> _history;
};

#endif // HISTORYMANAGER_H
