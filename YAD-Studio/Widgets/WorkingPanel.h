#ifndef WORKINGPANEL_H
#define WORKINGPANEL_H
#include "Logic/FunctionsStorage.h"
#include <QWidget>

namespace Ui {
class WorkingPanel;
}

class WorkingPanel : public QWidget
{
    Q_OBJECT

public:
    explicit WorkingPanel(QWidget *parent = 0);
    ~WorkingPanel();
public slots:
    void onFunctionActive(FunctionPtr function);
private:
    Ui::WorkingPanel *ui;
};

#endif // WORKINGPANEL_H
