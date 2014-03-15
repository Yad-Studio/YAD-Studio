#include "MarkovAlphabet.h"

MarkovAlphabet::MarkovAlphabet(const QSet<QChar> &alphabeth):
    _chars(alphabeth), _all_chars('$'), _is_auto(false)
{
    foreach (QChar ch, _chars)
    {
        _all_chars += ch;
    }
}
MarkovAlphabet::MarkovAlphabet(const bool is_auto)
    : _is_auto(is_auto)
{

}

QSet<QChar> MarkovAlphabet::getAlphabet() const
{
    return _chars;
}

QString MarkovAlphabet::getAllChars() const
{
    return _all_chars;
}
bool MarkovAlphabet::isAuto() const
{
    return _is_auto;
}
QString MarkovAlphabet::getSource() const
{
    return _source;
}
void MarkovAlphabet::setSource(QString source)
{
    _source = source;
}

bool MarkovAlphabet::isInAlphabet(QChar c) const
{
    //empty symbol
    if(c=='$' || _is_auto)
        return true;

    return _chars.find(c) != _chars.end();
}
