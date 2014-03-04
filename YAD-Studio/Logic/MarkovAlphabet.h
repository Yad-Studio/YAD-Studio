#ifndef MARKOVALPHABET_H
#define MARKOVALPHABET_H
#include <qvector.h>

class MarkovAlphabet
{
public:
    MarkovAlphabet(const QVector<char>& alphabeth);

    bool isInAlphabet(char c);
private:
    QVector<char> _chars;
};

#endif // MARKOVALPHABET_H
