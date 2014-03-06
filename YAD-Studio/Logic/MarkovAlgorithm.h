#ifndef MARKOVALGORITHM_H
#define MARKOVALGORITHM_H
#include "MarkovAlphabet.h"
#include "MarkovRule.h"
#include <QVector>

class MarkovAlgorithm
{
public:

    /**
     * @brief The result of check whether the rule is part of the word or not.
     * If it is valid the has the position where the matching happens.
     */
    struct RuleFitResult
    {
        /**
         * @brief Creates result.
         *
         * EXAMPLE: Word: aaaabbb
         * Rule ab -> c
         * start_index = 3
         * length = 2
         *
         * EXAMPLE: Word: bbbbbbb
         * Rule ab -> c
         * start_index = -1
         * length = -1
         *
         * @param start_index
         * @param length
         */
        RuleFitResult(int start_index,
                      int length);

        /**
         * @brief index of char in the word which matches the rule
         */
        int start_index;

        /**
         * @brief length of the matching
         */
        int length;

        /**
         * @brief if the matching was not found this method will return false
         * @return
         */
        bool isValid() const;
    };

    /**
     * @brief Checks if rule fits the word
     * @param input_word word
     * @param rule rule
     * @return
     */
    static RuleFitResult isRuleFits(QString input_word, const MarkovRule& rule);

    static QString useRule(QString input_word, const MarkovRule& rule);
    /**
     * @brief Creates algorithm
     * @param alphabet alphabet
     * @param rules list of rules
     */
    MarkovAlgorithm(MarkovAlphabet alphabet=MarkovAlphabet(),
                    QVector<MarkovRule> rules=QVector<MarkovRule>());

    /**
     * @brief finds the rule which can be applied for input. If no rule found then nullptr is returned
     * @param input word for which rule will be found
     * @return
     */
    const MarkovRule* getRuleFor(QString input) const;

    /**
     * @brief Returns alphabet
     * @return
     */
    const MarkovAlphabet& getAlphabet() const;

    /**
     * @brief Returns list of rules
     * @return
     */
    QVector<MarkovRule> getRules() const;
private:

    /**
     * @brief alphabet
     */
    MarkovAlphabet _alphabet;
    /**
     * @brief list of rules
     */
    QVector<MarkovRule> _rules;

};

#endif // MARKOVALGORITHM_H
