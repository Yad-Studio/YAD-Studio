#ifndef RUNWIDGET_H
#define RUNWIDGET_H

#include "Logic/RunError.h"
#include <QWidget>

namespace Ui {
class RunWidget;
}

class RunWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RunWidget(QWidget *parent = 0);
    ~RunWidget();
    
private:
    Ui::RunWidget *ui;
public slots:
    void runStarted(QString input_word);

    void runStepsMade(int steps_make);

    void runSuccess(QString input_word,
                    QString output_word,
                    int steps_made);

    void runFailed(QString input_word,
                   RunError error,
                   int steps_made);
};

#endif // RUNWIDGET_H
