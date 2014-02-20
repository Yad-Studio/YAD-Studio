#ifndef FUNCTION_H
#define FUNCTION_H
#include "Term.h"
#include <QString>
#include <QObject>
#include <QVector>

class Function;
typedef std::shared_ptr<Function> FunctionPtr;
typedef QVector<FunctionPtr> FunctionPtrList;

typedef QString Comment;
/**
 * @brief Represents one function. Example: g(a,b) Has next fields:
 */
class Function : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Function can have two types
     */
    enum class Type
    {
        /**
        * @brief normal function has one base term
        */
        Normal,

        /**
        * @brief the function has two terms.
        * g(0, x) - base of recursion, g(y+1, x) - main term
        */
        Recursive
    };

signals:
    void typeChanged(const Type);
    void IDChanged(const FunctionID);
    void functionNameChanged(const FunctionName);
    void mainTermChanged(const TermPtr);

    /**
     * @brief signal is called when the number of arguments
     * is changed or the name of variables is changed
     */
    void argumentsListChanged(const Arguments);
    void recursionBaseTermChanged(const TermPtr);
    void commentChanged(const Comment);
public:




    /**
     * @brief Creates empty function
     * @return Autorelease pointer to function
     */
    static FunctionPtr create();

    /**
     * @brief See Type
     */
    void setType(const Type);

    /**
     * @brief Sets the ID for function
     * @param id should be unique numeric identifier for
     * function in current project
     */
    void setID(const FunctionID id);

    /**
     * @brief setFunctionName
     * @param name the name should be unique among functions in project
     */
    void setFunctionName(const FunctionName& name);

    /**
     * @brief the main term of the function
     */
    void setMainTerm(const TermPtr&);

    /**
     * @brief The list with names of arguments
     */
    void setArgumentsList(const Arguments&);

    /**
     * @brief The base term for recursion
     * (ONLY when Type==Recursive)
     */
    void setRecursionBaseTerm(const TermPtr&);

    /**
     * @brief setComment
     * @param comment for function
     */
    void setComment(const Comment& commnet);

    const Type getType() const;
    const FunctionID getID() const;
    const FunctionName& getName() const;
    const TermPtr& getMainTerm() const;
    const TermPtr& getRecursionBaseTerm() const;
    const Comment& getComment() const;

    /**
     * @brief Return the number of arguments of the function
     * @return
     */
    const unsigned int getArgumentsNumber() const;

private:


    Type _type;
    FunctionID _id;
    FunctionName _name;
    TermPtr _main_term;
    Arguments _arguments_list;

    //_type == Recursive
    TermPtr _base_term;

    Comment _comment;

    Function();
};

#endif // FUNCTION_H
