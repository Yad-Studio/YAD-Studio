#include "YadFile.h"
#include <QDebug>
YadFile::YadFile(
        QString source_code,
        QVector<QString> history)
    : _source_code(source_code),
      _history(history)
{

}

QString YadFile::getSourceCode() const
{
    return _source_code;
}


QVector<QString> YadFile::getHistory() const
{
    return _history;
}

void YadFile::saveToFile(QString file_name) const
{
    qDebug() << "Saved to file: " << file_name;
}


YadFile YadFile::readFromFile(QString file_name)
{
    qDebug() << "Read from file: " << file_name;

    QString source = "//Comment\nT = {a,b, c}\n aa->b \n bb->a\n\n";
    QVector<QString> history;
    history.push_back("aaaaabbbb");
    history.push_back("aaabb");

    return YadFile(source, history);
}
