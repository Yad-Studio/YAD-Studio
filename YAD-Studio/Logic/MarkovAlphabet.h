#ifndef MARKOVALPHABET_H
#define MARKOVALPHABET_H

#include <QSet>
#include <QChar>

class MarkovAlphabet
{
public:
    MarkovAlphabet(const QSet<QChar>& alphabeth=QSet<QChar>());

    bool isInAlphabet(QChar c) const;
private:
    QSet<QChar> _chars;
};

#endif // MARKOVALPHABET_H
