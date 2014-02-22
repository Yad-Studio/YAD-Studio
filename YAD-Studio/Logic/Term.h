#ifndef TERM_H
#define TERM_H

#include <memory>
#include <vector>
#include <string>
#include <QString>
#include <QVector>
#include <QObject>

class Term;
typedef QString FunctionName;
typedef int FunctionID;
typedef int VariableIndex;
typedef QString ArgumentName;
typedef QVector<ArgumentName> Arguments;
typedef std::shared_ptr<Term> TermPtr;
typedef QVector<TermPtr> TermPtrList;
typedef int ArgumentID;
/**
 * @brief Computable unit which can be computed if the initial values are given
 */
class Term : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The term can have multiple types.
     * The type defines how the term will be computed
     */
    enum class Type
    {
        /**
        * @brief term will take the value of a given variable
        */
        Variable,

        /**
        * @brief the function will be evaluated and the result
        * of term will be the result of function
        */
        Function,

        /**
        * @brief the flag which signals that the parent
        * function must be minimized by given variable
        */
        Variable_Min,

        /**
        * @brief the term which evaluates as zero
        */
        Zero
    };
signals:
    void functionIDChanged(const FunctionID);
    void termsNumberChanged(const unsigned int number);
    void termChanged(const ArgumentID id, const TermPtr new_term);
    void variableIndexChanged(const VariableIndex);

public:

    /**
     * @brief Creates an empty term
     * @param type The type of term @see Type . Can't be changed
     * when object is created
     * @return The object is auto released
     */
    static TermPtr create(const Type type);

    /**
     * @brief the id of function which must be called
     * (type=Function ONLY)
     */
    void setFunctionID(const FunctionID&);

    /**
     * @brief Set term for a given argument
     * (type==Function ONLY)
     * @param id argument id
     * @param term new term
     */
    void setTerm(const ArgumentID id, const TermPtr& term);

    /**
     * @brief the number of argument of evaluated function which value this term will take (Projection)
     * (type=Variable ONLY)
     */
    void setVariableIndex(const VariableIndex);

    /**
     * @brief @see Type
     * @return
     */
    const Type getType() const;

    /**
     * @brief @see setFunctionID
     * (type=Function ONLY)
     * @return
     */
    const FunctionID getFunctionID() const;

    /**
     * @brief @see setTerm
     * (type=Function ONLY)
     * @return
     */
    const TermPtr& getTerm(const ArgumentID term_id) const;

    const unsigned int getTermsNumber() const;

    /**
     * @brief @see setVariableIndex
     * (type=Variable ONLY)
     * @return
     */
    const VariableIndex getVariableIndex() const;
private:
    Term(const Type type);




    Type _type;

    //_type == Function
    FunctionID _function_id;
    //_type == Function
    TermPtrList _terms_list;

    //_type == Variable
    VariableIndex _variable_index;

    //_type == Function
    int _term_number;
private slots:
    void argumentsNumberChanged(const unsigned int number);
};


#endif // TERM_H
