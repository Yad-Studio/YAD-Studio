#ifndef MYMODULE_H
#define MYMODULE_H

#include <QObject>

class MyModule : public QObject
{
    Q_OBJECT
public:
    explicit MyModule(QObject *parent = 0);

signals:
    void mySignal(int number, QString string);

public slots:
    void onAction();
};

#endif // MYMODULE_H
