#ifndef MARKOVALPHABET_H
#define MARKOVALPHABET_H

#include <QSet>
#include <QChar>
#include <QString>

class MarkovAlphabet
{
public:
    MarkovAlphabet(const QSet<QChar>& alphabeth=QSet<QChar>());

    bool isInAlphabet(QChar c) const;
    QSet<QChar> getAlphabet() const;

    QString getAllChars() const;
private:
    QSet<QChar> _chars;
    QString _all_chars;
};

#endif // MARKOVALPHABET_H
