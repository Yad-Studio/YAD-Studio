#ifndef YADFILE_H
#define YADFILE_H
#include <QVector>
#include <QString>

/**
 * @brief Saves and loads data from file
 */
class YadFile
{
public:
    /**
     * @brief YadFile
     * @param source_code complete source code (with comments)
     * @param history history of launches
     */
    YadFile(QString source_code,
            QVector<QString> history);

    /**
     * @brief Returns source code
     * @return
     */
    QString getSourceCode() const;

    /**
     * @brief Returns history of launches
     * @return
     */
    QVector<QString> getHistory() const;

    /**
     * @brief  method saves to file source code and history to a given file.
     * When any error occurs then
     * the method should throw QException with error description
     * @param file_name
     */
    void saveToFile(QString file_name) const;

    /**
     * @brief  method reads source code and history from file.
     * When any error occurs then the method should throw
     * QException with error description
     * @param file_name
     * @return
     */
    static YadFile readFromFile(QString file_name);
private:


    /**
     * @brief complete source code (with comments)
     */
    QString _source_code;
    /**
     * @brief history of launches
     */
    QVector<QString> _history;

};

#endif // YADFILE_H
