#ifndef COMPILERERROR_H
#define COMPILERERROR_H
#include "QString"

class CompilerError
{
public:
    CompilerError( const QString& title="",
                   const QString& description="",
                   int error_number=-1,
                   int line_numer=-1);

    int getErrorNumber();
    int getLineNumber();
    const QString& getErrorTitle();
    const QString& getErrorDescription();
    /**
     * @brief getFullErrorInfo
     * @return ErrorTitle + ErrorDescription
     */
    const QString getFullErrorInfo();

    void setErrorNumber(int number);
    void setLineNumber(int line);
    void setErrorTitle(const QString& title);
    void setErrorDescription(const QString& description);

private:
    // each error type has own number
    int _error_number;

    //number of line, where the error was occurred
    int _line_numer;

    QString _title;
    QString _description;
};

#endif // COMPILERERROR_H
