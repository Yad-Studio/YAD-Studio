#ifndef DEBUGRUNWIDGET_H
#define DEBUGRUNWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

#include "Logic/MarkovRule.h"
#include "Logic/RunError.h"

namespace Ui {
class DebugRunWidget;
}

class DebugRunWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DebugRunWidget(QWidget *parent = 0);
    ~DebugRunWidget();
    
private:
    Ui::DebugRunWidget *ui;
    bool _debug_pause;
public slots:

    //should clear all previously set data
    //and prepare to new debug session.
    //If the widget is hidden it should show itself.
    void debugStarted(QString input_word);

    //widget should go to state 1 and fill in received info.
    void debugSuccess(QString input_word,
                 QString output_word,
                 int steps_made);

    //widget should go to state 2 and display received info.
    void debugFailed(QString input_word,
                RunError error,
                int steps_made);

    // widget should go to state 4.
    //Add info to Debug Log about this rule and fill in all information.
    void debugStepFinished(int step_number,
                      QString before_rule_applied,
                      QString after_rule_applied,
                      MarkovRule applied_rule);

    //when this slot is called only after debugStepFinished.
    //So the widget is in state 4 and should transform to state 3
    //by showing buttons.
    void breakPointReached(int line_number);

    /**
     * @brief colorWord
     * @param word
     * @param sub_str
     * @return find subString in String and color it
     */
    const QString colorWord(const QString &word,
                            MarkovRule &applied_rule,
                            const QString &color);

    const QString colorWord(const QString &word,
                                        int begin,
                                        int length,
                                        const QString &color);

    void onContinueButtonClicked();
    void onNextButtonClicked();
    void onStopButtonCliked();

    void onCloseButtonClicked();

signals:
    //the signal should be triggered when Next Step button is clicked.
    //When this signal is triggered then removeBreakPoint()
    //also must be triggered.
    //Note widget should not do any other activity and must wait
    //until any slots will be called.
    void nextStepClicked();

    //the signal should be triggered when Continue button is clicked.
    //When this signal is triggered then removeBreakPoint() also must be
    //triggered. Note widget should not do any other activity and
    //must wait until any slots will be called.
    void continueClicked();

    //the signal should be triggered when Stop button is clicked.
    //When this signal is triggered then removeBreakPoint() also must be
    //triggered. Note widget should not do any other activity and must
    //wait until any slots will be called.
    void stopClicked();

    //this signal will notify the TextEdit to line with break point
    //highlighting.
    void removeBreakPoint();

    //notifies the text edit that debug stopped at given number.
    //This signal should be emitted when the breakPointReached slot
    //is called.
    void showBreakPoint(int line_number);
protected:
    void paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
};

#endif // DEBUGRUNWIDGET_H
