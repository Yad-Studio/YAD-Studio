#include "MarkovAlphabet.h"

MarkovAlphabet::MarkovAlphabet(const QVector<char> &alphabeth):
    _chars(alphabeth)
{
}
bool MarkovAlphabet::isInAlphabet(char c)
{
    //empty symbol
    if(c=='$')
        return true;
    for(unsigned int i=0; i<_chars.size(); ++i)
    {
        if(_chars[i] == c)
            return true;
    }
    return false;
}
