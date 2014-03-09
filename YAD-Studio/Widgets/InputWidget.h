#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class InputWidget;
}

class InputWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit InputWidget(QWidget *parent = 0);
    ~InputWidget();

public slots:

    //is called when the algorithm is starting running,
    //the button Run and Run with debug should be disabled
    void runStarted();

    //is called when the algorithm is finished running,
    //the buttons Run and Run with debug MAY be enabled
    void runFinished();

    //the value of Input Word should be changed to new value.
    void setInput(QString new_input_word);

    // when true is received and runStarted has not been called then Run
    //and Run with debug should become enabled.
    //When false is received then Run and Run with debug
    //should be disabled
    void canRunAlgorithm(bool can_run);

    void runCliked();
    void runWithDebugClicked();
    void saveCliked();

signals:
    //should be emitted when user clicks run.
    //The value of Input Word field should be passed as argument
    void run(QString input_word);

    //the same as previous but when the Run with debug button is clicked.
    void runWithDebug(QString input_word);

    //when button is clicked
    void save();

    //should be emitted when run or runWithDebug is emitted.
    //Used to notify HistoryStorage about new word.
    void addToHistory(QString input_word);
    
private:
    Ui::InputWidget *ui;

    bool _can_run_algorythm;
protected:
    void paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

};

#endif // INPUTWIDGET_H
