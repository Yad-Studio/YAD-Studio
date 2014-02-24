#ifndef FUNCTIONSSTORAGE_H
#define FUNCTIONSSTORAGE_H
#include <QObject>
#include <QMap>
#include <QSignalMapper>

#include "Function.h"
class FunctionsStorage : public QObject
{
    Q_OBJECT
public:
    static FunctionID S;

    /**
     * @brief Returns the main Storage Instance
     * @return
     */
    static FunctionsStorage* getInstance();

    /**
     * @brief Returns function by id
     * if function not found the nullptr is returned
     * @param id
     * @return
     */
    FunctionPtr getFunction(const FunctionID id);

    /**
     * @brief addFunction to function list.
     * if function id == 0 then the automatic ID will be assigned to function
     * @param function
     */
    void addFunction(FunctionPtr function);

    const QVector<TermPtr>& getSystemTerms();

    /**
     * @brief getAllUserFunctions
     * @return all user functions, except system functions
     */
    const QVector<FunctionID> getAllUserFunctions();
signals:
    void onFunctionChanged(int);
    void onNewFunctionAdded(int);
    void onFunctionDeleted(int);

private:
    static FunctionID st_next_id;
    typedef QMap<FunctionID, FunctionPtr> FunctionMap;
    QSignalMapper _mapper;
    FunctionMap _function_storage;

    FunctionsStorage();

    QVector<TermPtr> _system_terms;
};

#endif // FUNCTIONSSTORAGE_H
