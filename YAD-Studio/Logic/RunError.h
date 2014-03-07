#ifndef RUNERROR_H
#define RUNERROR_H
#include "QString"

class RunError
{
public:
    RunError(const QString& title, const QString& description,
             int error_numer);

    int getErrorNumber();
    const QString& getErrorTitle();
    const QString& getErrorDescription();
    /**
     * @brief getFullErrorInfo
     * @return ErrorTitle + ErrorDescription
     */
    const QString getFullErrorInfo();

    void setErrorNumber(int number);
    void setErrorTitle(const QString& title);
    void setErrorDescription(const QString& description);
private:
    // each error type has own number
    int _error_number;

    QString _title;
    QString _description;
};

#endif // RUNERROR_H
