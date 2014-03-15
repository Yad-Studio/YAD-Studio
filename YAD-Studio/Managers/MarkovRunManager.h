#ifndef MARKOVRUNMANAGER_H
#define MARKOVRUNMANAGER_H
#include <QObject>
#include "Logic/MarkovAlgorithm.h"
#include "Logic/RunError.h"
#include "QSet"
#include "QHash"


class StepResult
{
public:
    StepResult(QString output,
               int step_id):
        _output(output),
        _step_id(step_id)
    {
    }

    QString _output; //The word after rule on this step was applied
    int _step_id; //The id of step
};
bool operator <(const StepResult& a, const StepResult& b);
bool operator==(const StepResult& a, const StepResult& b);

inline uint qHash(const StepResult& a)
{
     return qHash(a._output);
}

class MarkovRunManager: public QObject
{
    Q_OBJECT
public:
    static MarkovRunManager* getInstance();

private:
    MarkovRunManager();
    MarkovRunManager(MarkovRunManager const&);
    void operator=(MarkovRunManager const&);

    static MarkovRunManager* _instance;

    //the alphabet and rules list.
    //It can be changed while algorithm is running.
    MarkovAlgorithm _algorithm;

    //the input word of last run.
    QString _input_word;

    //the number of steps made.
    int _steps_made;

    //the word after last rule was applied
    QString _word_after_last_step;

    //break points.
    QSet<int> _break_points;

    //stores each step result to prevent program from cycle.
    QSet<StepResult> _steps_history;

    //whether the program now in debug mode.
    bool _is_debug_mode;

    //This function return true if the next should be made and false otherwise.
    bool findAndApplyNextRule();

    bool _stop_on_next_step;

    int getStepNumberOfValue(QString word);
    bool choseAndUseRule(QString &word, MarkovRule &rule);
    bool _terminate_on_next_step;

    void doStartDebug(QString word, bool stop_at_first_step);

    bool isInputValid(QString input_word);
public slots:
    //called when new compiled algorithm is available.
    void setAlgorithm(MarkovAlgorithm algorithm);

    //true if the last version of source code is ready for running.
    //When changed the canRunSourceCode should be emited.
    void setCanRunSourceCode(bool can);

    //starts running process.
    void runWithoutDebug(QString input_word);

    //starts running with debug.
    void runWithDebug(QString input_word);

    void runWithDebugStepByStep(QString input_word);

    // add break point to set
    void addBreakPoint(int line_number);

    //removes break point from set
    void removeBreakPoint(int line_number);

    //called when user clicks Next Step in debug window.
    void debugNextStep();

    //called when user clicks Continue in debug window
    void debugContinue();

    //called when user clicks Stop in debug window
    void debugStop();


    void terminateRun();
signals:
    //emited when setCanRunSourceCode is called
    void canRunSourceCode(bool);

    void runWithoutDebugStarted(QString input_word);

    void runWithoutDebugFinishSuccess(QString input_word,
                                      QString output_word,
                                      int steps_made);

    void runWithoutDebugFinishFail(QString input_word,
                                   RunError error,
                                   int steps_made);

    void runStepsMade(int steps_made);

    void debugStarted(QString input_word);

    void debugFinishSuccess(QString input_word,
                            QString output_word,
                            int steps_made);

    void debugFinishFail(QString input_word,
                         RunError error,
                         int steps_made);

    void debugStepFinished(int step_number,
                           QString before_step,
                           QString after_step,
                           MarkovRule rule);

    void debugBreakPointReached(int line_number);
};




#endif // MARKOVRUNMANAGER_H
