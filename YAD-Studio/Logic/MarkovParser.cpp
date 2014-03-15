#include "MarkovParser.h"
#include <QStringList>
#include <QDebug>

namespace Parser
{
    static QString forbidden_symbols(">-. TI={}");
}
using namespace Parser;

QString removeComments(QString line)
{
    int comments_index = line.indexOf("//");
    if(comments_index >= 0)
        return line.mid(0, comments_index);
    return line;
}

QString trim(QString line)
{
    return line.trimmed();
}

CompilerError wrongAlphabetChar(int line, QString letter)
{
    QString title=QObject::tr("Symbol '%1' can't be used in alphabet").arg(letter);
    QString description=QObject::tr("In alphabet can be used only characters. Examples: 'T = {a, b, c, d}'.");

    return CompilerError(title, description, 201, line);
}

CompilerError charAlreadyInAlphabet(int line, QString letter)
{
    QString title=QObject::tr("Symbol '%1' added to alphabet more than once").arg(letter);
    QString description=QObject::tr("Each symbol can be added to alphabet only once. Examples: 'T = {a, b, c, d}'.");

    return CompilerError(title, description, 204, line);
}

CompilerError emptySymbolInAlphabet(int line)
{
    QString title=QObject::tr("Symbol '$' can't be added to alphabet");
    QString description=QObject::tr("'$' means an empty symbol and is already a part of alphabet.");

    return CompilerError(title, description, 201, line);
}

CompilerError forbiddenInAlphabet(int line, QString letter)
{
    QString title=QObject::tr("Symbol '%1' is forbidden to be used in alphabet").arg(letter);
    QString description=QObject::tr("You can use any other symbol. Examples: 'T = {a, b, c, d}'.");

    return CompilerError(title, description, 205, line);
}

CompilerError notInAlphabet(int line, QString letter, MarkovAlphabet alphabet)
{

    QString title=QObject::tr("Symbol '%1' is not in alphabet").arg(letter);
    QString description=QObject::tr("You can add it to alphabet. Examples: 'T = {%1, %2}'.")
            .arg(letter, alphabet.getSource());

    return CompilerError(title, description, 200, line);
}

CompilerError forbiddenInRule(int line, QString letter)
{
    QString title=QObject::tr("Symbol '%1' can't be used in rule").arg(letter);
    QString description=QObject::tr("You can use any other symbol which are in alphabet.");

    return CompilerError(title, description, 200, line);
}

CompilerError wrongRuleDefenition(int line, QString text)
{
    QString title=QObject::tr("Wrong rule definition");
    QString description=QObject::tr("Definition of rule is wrong. ('%1'). Example: 'aa -> bb' or 'aa ->. bb'").arg(text);

    return CompilerError(title, description, 203, line);
}

CompilerError noAlphabetDefenition(int line)
{
    QString title=QObject::tr("Alphabet definition is not found");
    QString description=QObject::tr("Alphabet definition example: 'T = {a,b,c}'");

    return CompilerError(title, description, 202, line);
}

bool isCharsInAlphabet(int line_number, QString text,
                       QVector<CompilerError>& errors,
                       MarkovAlphabet& alphabet)
{
    text = text.replace("$", "");

    bool res = true;
    for(int i = 0; i<text.size(); ++i)
    {
        QChar ch = text[i];
        if(!alphabet.isInAlphabet(ch))
        {
            if(forbidden_symbols.indexOf(ch) >= 0)
                errors.push_back(forbiddenInRule(line_number, ch));
            else
                errors.push_back(notInAlphabet(line_number, ch, alphabet));

            res = false;
            break;
        }
    }
    return res;
}

void parseRule(int line_number, QString line,
               QVector<CompilerError>& errors,
               QVector<MarkovRule>& rules,
               MarkovAlphabet& alphabet)
{
    static QRegExp rx_rule("^([^\\.\\->]+)(->[\\.]*)([^\\.\\->]+)$");

    //Read rule
    int pos = rx_rule.indexIn(line);
    if(pos < 0)
    {
        errors.push_back(wrongRuleDefenition(line_number, line));
    }
    else
    {
        QString left_part = trim(rx_rule.cap(1));
        QString right_part = trim(rx_rule.cap(3));

        if(isCharsInAlphabet(line_number, left_part, errors, alphabet)
                && isCharsInAlphabet(line_number, right_part, errors, alphabet))
        {
            QString mid = trim(rx_rule.cap(2));
            bool is_final = mid=="->.";
            MarkovRule rule(left_part, right_part, is_final, line_number);
            rules.push_back(rule);
#ifndef QT_NO_DEBUG
            qDebug() << "Rule: " << left_part << is_final << right_part;
#endif
        }

    }
}

bool parseAlphabet(int line_number,
                   QString line,
                   QVector<CompilerError>& errors,
                   MarkovAlphabet& alphab,
                   QString alphabet_mark)
{
    QRegExp rx_alphabet("^"+alphabet_mark+"[\\s]*=[\\s]*\\{([^\\{\\}]*)\\}$");


    bool res = false;
    //Read alphabet
    int pos = rx_alphabet.indexIn(line);
    if(pos < 0)
    {
        //Error
        res = false;
        //errors.push_back(noAlphabetDefenition(line_number));
    }
    else
    {
        QString letters_str = trim(rx_alphabet.cap(1));
#ifndef QT_NO_DEBUG
        qDebug() << "Letters: " << letters_str;
#endif
        QSet<QChar> alphabet_q;
        if(letters_str.size() > 0)
        {
            QStringList letters = letters_str.split(",");
            for(int j=0; j<letters.size(); ++j)
            {
                QString letter = trim(letters[j]);

                if(letter.size() != 1)
                {
                    errors.push_back(wrongAlphabetChar(line_number, letter));
                }
                else if(letter == "$")
                {
                    errors.push_back(emptySymbolInAlphabet(line_number));
                }
                else if(forbidden_symbols.indexOf(letter) >= 0)
                {
                    errors.push_back(forbiddenInAlphabet(line_number, letter));
                }
                else
                {
                    //alphabet.push_back(letter);
                    QChar ch = letter[0];
                    if(alphabet_q.find(ch) != alphabet_q.end())
                    {
                        errors.push_back(charAlreadyInAlphabet(line_number, letter));
                    }
                    else
                    {
                        alphabet_q.insert(ch);
                    }
                }
            }
        }

        alphab = MarkovAlphabet(alphabet_q);
        alphab.setSource(letters_str);
        res = true;
#ifndef QT_NO_DEBUG
        qDebug() << "Alphabet: " << alphabet_q;
#endif
    }
    return res;
}

bool MarkovParser::parseSourceCode(QString source_code,
                                   MarkovAlgorithm& algorithm,
                                   QVector<CompilerError>& errors)
{
    bool first_rule_is_readed = false;
    bool T_alphabet = false;
    bool I_alphabet = false;
    QStringList lines = source_code.split(QRegExp("[\r\n]"));



    errors.clear();

    //QVector<QString> alphabet;
    MarkovAlphabet alphabet(true);
    MarkovAlphabet input_alphabet(true);
    QVector<MarkovRule> rules;

    for(int i=0; i<lines.size(); ++i)
    {
        int line_number = i + 1;
        QString line = trim(removeComments(lines[i]));

        if(line.size() > 0)
        {
            bool readed = false;
            if(!first_rule_is_readed)
            {
                if(!T_alphabet)
                {
                    T_alphabet = parseAlphabet(line_number, line, errors, alphabet, "T");
                    readed = T_alphabet;
                }
                else if(!I_alphabet)
                {
                    I_alphabet = parseAlphabet(line_number, line, errors, input_alphabet, "I");

                    foreach(QChar ch, input_alphabet.getAlphabet())
                    {
                        if(!alphabet.isInAlphabet(ch))
                        {
                            errors.push_back(notInAlphabet(line_number, ch, alphabet));
                            break;
                        }
                    }

                    readed = I_alphabet;
                }
            }

            if(!readed)
            {
                parseRule(line_number, line, errors, rules, alphabet);
                first_rule_is_readed = (rules.size() > 0);
            }

        }
    }

    algorithm = MarkovAlgorithm(alphabet, rules, input_alphabet);

    return errors.size() == 0;
}
