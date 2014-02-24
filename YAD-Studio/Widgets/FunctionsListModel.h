#ifndef FUNCTIONSLISTMODEL_H
#define FUNCTIONSLISTMODEL_H
#include "Logic/FunctionsStorage.h"
#include <QAbstractListModel>

class FunctionsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FunctionsListModel(FunctionPtr parent_function,
                                QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
//    bool insertRows(int position, int rows,
//                    const QModelIndex &parent = QModelIndex());
//    bool removeRows(int position, int rows,
//                    const QModelIndex &parent = QModelIndex());


    //QModelIndex getTermIndex(TermPtr term);
    TermPtr getTerm(const int) const;
signals:
    
public slots:
    
private:
    QVector<TermPtr> _variables;
    QVector<TermPtr> _system_functions;
    QVector<TermPtr> _functions;

    FunctionPtr _parent_function;

    QString termToString(TermPtr term) const ;
private slots:
    //void argumentsNumberChanged(const unsigned int number);
    //void argumentNameChanged(const ArgumentID id, const ArgumentName new_name);

};

#endif // FUNCTIONSLISTMODEL_H
