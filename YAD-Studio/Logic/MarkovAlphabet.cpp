#include "MarkovAlphabet.h"

MarkovAlphabet::MarkovAlphabet(const QSet<QChar> &alphabeth):
    _chars(alphabeth)
{
}
bool MarkovAlphabet::isInAlphabet(QChar c) const
{
    //empty symbol
    if(c=='$')
        return true;

    return _chars.find(c) != _chars.end();
}
