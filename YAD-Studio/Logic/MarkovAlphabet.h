#ifndef MARKOVALPHABET_H
#define MARKOVALPHABET_H

#include <QSet>
#include <QChar>
#include <QString>

class MarkovAlphabet
{
public:
    MarkovAlphabet(const QSet<QChar>& alphabeth=QSet<QChar>());
    MarkovAlphabet(const bool is_auto);

    bool isInAlphabet(QChar c) const;
    QSet<QChar> getAlphabet() const;

    QString getAllChars() const;
    QString getSource() const;
    void setSource(QString source);

    bool isAuto() const;
private:
    QSet<QChar> _chars;
    QString _all_chars;
    QString _source;
    bool _is_auto;
};

#endif // MARKOVALPHABET_H
