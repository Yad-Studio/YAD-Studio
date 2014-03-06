#include "MarkovRunManager.h"


MarkovRunManager* MarkovRunManager::_instance = nullptr;

MarkovRunManager* MarkovRunManager::getInstance( )
{
      if (_instance == nullptr)
        _instance = new MarkovRunManager();
     return _instance;
}

MarkovRunManager::MarkovRunManager():
        _input_word(""),
        _steps_made(0),
        _word_after_last_step(""),
        _is_debug_mode(false)
{
}
int MarkovRunManager::getStepNumberOfValue(QString word)
{
    QSet<StepResult>::iterator i;
    for (i = _steps_history.begin(); i != _steps_history.end(); ++i)
    {
        StepResult curr = *i;
        if(curr._output == word)
            return curr._step_id;
    }
    return -1;
}
bool MarkovRunManager::choseAndUseRule(QString& word,
                                       MarkovRule& rule)
{
    //get rule
    const MarkovRule*  markov_rule = _algorithm.getRuleFor(word);
    rule = *markov_rule;

    QString res="";

    //use rule
    if(markov_rule != nullptr)
    {
        res = _algorithm.useRule(word,rule);
        word = res;
        return true;
    }
    return false;
}


bool MarkovRunManager::findAndApplyNextRule()
{
    if (_steps_history.contains(StepResult(_word_after_last_step,0)))
    {
        if(_is_debug_mode)
        {
            int prev_same_stem = getStepNumberOfValue(_input_word);

            QString description = "The result of step#"+prev_same_stem;
            description+=" is same as on the step #";
            description+=_steps_made;

            RunError error("Algorithm never terminates",
                           description,
                           102);
            emit debugFinishFail(_input_word,error,_steps_made);
        }
        else
        {
            int prev_same_stem = getStepNumberOfValue(_input_word);

            QString description = "The result of step#"+prev_same_stem;
            description+=" is same as on the step #";
            description+=_steps_made;

            RunError error("Algorithm never terminates",
                           description,
                           102);
            emit runWithoutDebugFinishFail(_input_word,error,_steps_made);
        }

        return false;
    }

    if(_word_after_last_step.size()>2000)
    {
        if(_is_debug_mode)
        {
            QString description = "Result can not be longer than 2000 symbols. On step #"+_steps_made;
            description+=" input become ";
            description+=_word_after_last_step.size();

            RunError error("Too long result",
                           description,
                           101);
            emit debugFinishFail(_input_word,error,_steps_made);
        }
        else
        {
            QString description = "Result can not be longer than 2000 symbols. On step #"+_steps_made;
            description+=" input become ";
            description+=_word_after_last_step.size();

            RunError error("Too long result",
                           description,
                           101);
            emit runWithoutDebugFinishFail(_input_word,error,_steps_made);
        }
        return false;
    }

//Go through MarkovRules and select which fits.
//If there are no rules then emit debugFinishSuccess or
//runWithoutDebugFinishSuccess depending on run mode.
//Use as _word_after_last_step as output word.

    QString word = _word_after_last_step;
    MarkovRule rule;
    if(!choseAndUseRule(word, rule))
    {
        //there are no rules
        if(_is_debug_mode)
        {
            emit debugFinishSuccess(_input_word,
                                    word,
                                    _steps_made);
        }
        else
        {
            emit runWithoutDebugFinishSuccess(_input_word,
                                              word,
                                              _steps_made);
        }
    }

    ++_steps_made;

    if(_is_debug_mode)
    {
        emit debugStepFinished(_steps_made,
                               _word_after_last_step,
                               word,
                               rule);
    }

    _word_after_last_step = word;

    _steps_history.insert(StepResult(_word_after_last_step,_steps_made));


    if(_is_debug_mode)
    {
        if(_break_points.contains(rule.getLineNumber()))
        {
            emit debugBreakPointReached(rule.getLineNumber());
            return false;
        }
    }

//If rule is final then emit debugFinishSuccess or
//runWithoutDebugFinishSuccess depending on run mode.
//Use as _word_after_last_step as output word. return false.

    if(rule.isFinalRule())
    {
        if(_is_debug_mode)
        {
            emit debugFinishSuccess(_input_word,
                                    _word_after_last_step,
                                    _steps_made);
        }
        else
        {
            emit runWithoutDebugFinishSuccess(_input_word,
                                              _word_after_last_step,
                                              _steps_made);
        }
        return false;
    }

    return true;
}

void MarkovRunManager::setAlgorithm(MarkovAlgorithm algorithm)
{
    _algorithm = algorithm;
}

void MarkovRunManager::setCanRunSourceCode(bool can)
{
    emit canRunSourceCode(can);
}

void MarkovRunManager::runWithoutDebug(QString input_word)
{

}

void MarkovRunManager::runWithDebug(QString input_word)
{

}

void MarkovRunManager::addBreakPoint(int line_number)
{

}

void MarkovRunManager::removeBreakPoint(int line_number)
{

}

void MarkovRunManager::debugNextStep()
{

}

void MarkovRunManager::debugContinue()
{

}

void MarkovRunManager::debugStop()
{

}
bool operator<(const StepResult& a, const StepResult& b)
{
   return a._output < b._output;
}
bool operator==(const StepResult& a, const StepResult& b)
{
    return a._output == b._output;
}
