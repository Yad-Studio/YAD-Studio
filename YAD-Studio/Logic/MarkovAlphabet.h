#ifndef MARKOVALPHABET_H
#define MARKOVALPHABET_H

#include <QSet>
#include <QChar>

class MarkovAlphabet
{
public:
    MarkovAlphabet(const QSet<QChar>& alphabeth=QSet<QChar>());

    bool isInAlphabet(QChar c) const;
    QSet<QChar> getAlphabet() const;
private:
    QSet<QChar> _chars;
};

#endif // MARKOVALPHABET_H
