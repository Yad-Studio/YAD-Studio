#ifndef SOURCECODEMANAGER_H
#define SOURCECODEMANAGER_H
#include "QString"
#include <QObject>

class SourceCodeManager: public QObject
{
    Q_OBJECT
public:
    static SourceCodeManager* getInstance( );

    //returns the value of _source_code
    QString getSourceCode();

private:
    //the value which user inputs to the editor
    QString _source_code;
    static SourceCodeManager* _instance;

    //it is a singletone
    SourceCodeManager();
    SourceCodeManager(SourceCodeManager const&);
    void operator=(SourceCodeManager const&);

public slots:
    //called when somebody changes the source code.
    //new_source should be saved and sourceCodeChanged signal
    //should be emitted.
    void setSourceCode(QString new_source);

    //called when new source code was loaded from file.
    //The newSourceCodeWasLoaded should be emitted.
    void setNewSourceCodeFromFile(QString new_source);

signals:
    //emitted when the source code changed.
    void sourceCodeChanged(QString source_code);

    //emitted when the source code was loaded from file.
    void newSourceCodeWasLoaded(QString source_code);
};

#endif // SOURCECODEMANAGER_H
