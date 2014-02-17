#ifndef FUNCTIONSSTORAGE_H
#define FUNCTIONSSTORAGE_H
#include <QObject>

class FunctionsStorage : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Returns the main Storage Instance
     * @return
     */
    static FunctionsStorage* getInstance();

signals:
//    void onFunctionChanged(FunctionPtr);
//    void onNewFunctionAdded(FunctionPtr);
//    void onNewFunctionsAdded(FunctionPtrList);
//    void onFunctionDeleted(FunctionPtr);

private:
    FunctionsStorage();

    static FunctionsStorage _instance;
};

#endif // FUNCTIONSSTORAGE_H
