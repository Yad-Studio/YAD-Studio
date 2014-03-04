#include "RunError.h"

RunError::RunError(const QString& title,
                   const QString& description,
                   int error_numer):
    _title(title),
    _description(description),
    _error_number(error_numer)
{
}
int RunError::getErrorNumner()
{
    return _error_number;
}

const QString& RunError::getErrorTitle()
{
    return _title;
}

const QString& RunError::getErrorDescription()
{
    return _description;
}

const QString RunError::getFullErrorInfo()
{
    return _title + ": " + _description;
}

void RunError::setErrorNumber(int number)
{
    _error_number = number;
}
void RunError::setErrorTitle(const QString& title)
{
    _title = title;
}

void RunError::setErrorDescription(const QString& description)
{
    _description = description;
}
