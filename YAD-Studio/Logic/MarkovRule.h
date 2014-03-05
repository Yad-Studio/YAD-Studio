#ifndef MARKOVRULE_H
#define MARKOVRULE_H
#include "QString"

class MarkovRule
{
public:
    MarkovRule(const QString& left_patr="", const QString& right_part="",
               bool is_final = false, int line_number=-1);

    bool isFinalRule() const;
    const QString& getLeftPart() const;
    const QString& getRightPart() const;
    int getLineNumber() const;

    void setFinalRule(bool is_final);
    void setLeftPart(const QString& str);
    void setRightPart(const QString& str);
    void setLineNumber(int line_number);

private:
    //left part of the rule
    QString _pattern;
    //right part of the rule
    QString _substitution;

    //if rule is final then algorithm will stop after this rule execution
    bool _is_final_rule;

    //number of line where the rule was found
    int _line_number;
};

#endif // MARKOVRULE_H
