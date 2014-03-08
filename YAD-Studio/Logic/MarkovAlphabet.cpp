#include "MarkovAlphabet.h"

MarkovAlphabet::MarkovAlphabet(const QSet<QChar> &alphabeth):
    _chars(alphabeth), _all_chars('$')
{
    foreach (QChar ch, _chars)
    {
        _all_chars += ch;
    }
}

QSet<QChar> MarkovAlphabet::getAlphabet() const
{
    return _chars;
}

QString MarkovAlphabet::getAllChars() const
{
    return _all_chars;
}

bool MarkovAlphabet::isInAlphabet(QChar c) const
{
    //empty symbol
    if(c=='$')
        return true;

    return _chars.find(c) != _chars.end();
}
