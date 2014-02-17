#ifndef TERM_H
#define TERM_H

#include <memory>
#include <vector>
#include <string>

class Term;
typedef std::string FunctionName;
typedef int FunctionID;
typedef int VariableIndex;
typedef std::string ArgumentName;
typedef std::vector<ArgumentName> Arguments;
typedef std::shared_ptr<Term> TermPtr;
typedef std::vector<TermPtr> TermPtrList;

/**
 * @brief Computable unit which can be computed if the initial values are given
 */
class Term
{
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
     * @brief list which contains exact number of terms as the function
     * with function_id has parameters.
     * This terms will be evaluated and will be used as parameters
     * for this function
     * (type=Function ONLY)
     */
    void setTermList(const TermPtrList&);

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
     * @brief @see setTermList
     * (type=Function ONLY)
     * @return
     */
    const TermPtrList& getTermList() const;

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
};


#endif // TERM_H
