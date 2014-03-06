#ifndef MARKOVPARSER_H
#define MARKOVPARSER_H
#include "Logic/MarkovAlgorithm.h"
#include "Logic/CompilerError.h"

class MarkovParser
{
public:
    /**
     * @brief parses the source code
     * @param source_code code to parse
     * @param algorithm output algorithm
     * @param errors output errors
     * @return returns true if there are no errors and false otherwise.
     */
    static bool parseSourceCode(QString source_code,
                                MarkovAlgorithm& algorithm,
                                QVector<CompilerError>& errors);
private:
    MarkovParser();

};

#endif // MARKOVPARSER_H
