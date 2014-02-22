#ifndef FUNCTIONSSTORAGE_H
#define FUNCTIONSSTORAGE_H
#include <QObject>
#include <QMap>
#include "Function.h"
class FunctionsStorage : public QObject
{
    Q_OBJECT
public:
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
signals:
//    void onFunctionChanged(FunctionPtr);
//    void onNewFunctionAdded(FunctionPtr);
//    void onNewFunctionsAdded(FunctionPtrList);
//    void onFunctionDeleted(FunctionPtr);

private:
    static FunctionID st_next_id;
    typedef QMap<FunctionID, FunctionPtr> FunctionMap;

    FunctionMap _function_storage;

    FunctionsStorage();

    static FunctionsStorage _instance;
};

#endif // FUNCTIONSSTORAGE_H
