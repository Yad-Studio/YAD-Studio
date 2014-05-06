#include "YadFile.h"
#include <QDebug>
#include <QFile>
#include <QStringList>

YadFile::YadFile(
        QString source_code,
        QVector<QString> history)
    : _source_code(source_code),
      _history(history)
{

}
static QString history_start("//=========History========//");

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

    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString error = QObject::tr("Can't open file for writing.");
        throw std::runtime_error(error.toStdString().c_str());
    }

    QTextStream out(&file);
    out << _source_code << endl << endl << endl;

    out << history_start << endl;
    for(int i=0; i<_history.size(); ++i)
    {
        out << "//" << _history[i] << endl;
    }



}

QString rstrip(const QString& str)
{
    int n = str.size() - 1;
    for (; n >= 0; --n) {
        if (!str.at(n).isSpace()) {
            return str.left(n + 1);
        }
    }
    return "";
}


YadFile YadFile::readFromFile(QString file_name)
{
    qDebug() << "Read from file: " << file_name;

    QFile file(file_name);

    if(!file.exists())
    {
        QString error = QObject::tr("File does not exists.");
        throw std::runtime_error(error.toStdString().c_str());
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString error = QObject::tr("Can't open file.");
        throw std::runtime_error(error.toStdString().c_str());
    }

    QTextStream in(&file);
    QString content = in.readAll();

    int history_mark = content.indexOf(history_start);
    if(history_mark < 0)
    {
        QString error = QObject::tr("File is corrupted.");
        throw std::runtime_error(error.toStdString().c_str());
    }

    QString source = rstrip(content.mid(0,history_mark));
    QString history_line = content.mid(history_mark+history_start.size());

    qDebug() << "Source: " << source;
    qDebug() << "History: " << history_line;

    //QString source = "//Comment\nT = {a,b, c}\n aa->b \n bb->a\n\n";
    QVector<QString> history;

    QStringList lines = history_line.split(QRegExp("[\r\n]"));
    for(int i=0; i<lines.size(); ++i)
    {
        QString line = lines[i].trimmed();
        if(line.size() > 2 && line.mid(0,2)=="//")
        {
            history.push_back(line.mid(2));
        }
    }

    return YadFile(source, history);
}
