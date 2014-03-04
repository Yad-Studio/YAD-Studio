#include "CompilerError.h"

CompilerError::CompilerError(const QString &title,
                             const QString &description,
                             int error_number,
                             int line_numer):
    _title(title),
    _description(description),
    _error_number(error_number),
    _line_numer(line_numer)
{
}
int CompilerError::getErrorNumner()
{
    return _error_number;
}

int CompilerError::getLineNumber()
{
    return _line_numer;
}

const QString& CompilerError::getErrorTitle()
{
    return _title;
}

const QString& CompilerError::getErrorDescription()
{
    return _description;
}

const QString CompilerError::getFullErrorInfo()
{
    return _title + ": " + _description;
}

void CompilerError::setErrorNumber(int number)
{
    _error_number = number;
}

void CompilerError::setLineNumber(int line)
{
    _line_numer = line;
}

void CompilerError::setErrorTitle(const QString& title)
{
    _title = title;
}

void CompilerError::setErrorDescription(const QString& description)
{
    _description = description;
}
