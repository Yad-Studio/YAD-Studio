#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QString>
#include <QObject>
/**
 * @brief The class is responsible for saving files, listening for changes.
 */
class FileManager : public QObject
{
    Q_OBJECT
public:
    static FileManager* getInstance();

    /**
     * @brief returns whether there is unsaved data.
     * @return
     */
    bool hasUnsavedData();
public slots:
    /**
     * @brief opens the given file.
     * @param file_name
     */
    void openFile(QString file_name);

    /**
     * @brief display open file dialog and redirects the result to openFile.
     */
    void open();

    /**
     * @brief saves current changes to file.
     */
    bool save();

    /**
     * @brief saves file with new name. See the detailed description at the end.
     */
    bool saveAs();

    /**
     * @brief should start the new instance of the program.
     */
    void newFile();

    /**
     * @brief when the source code was changed. The _has_unsaved_data should be set to true.
     */
    void sourceCodeChanged();

    /**
     * @brief when the history was changed. The _has_unsaved_data should be set to true.
     */
    void historyChanged();
signals:

    /**
     * @brief emitted when the name of source file changed.
     * @param new_name
     */
    void fileNameChanged(QString new_name);

    /**
     * @brief emitted to notify whether there is unsaved data.
     * @param has_unsaved_data
     */
    void hasUnsavedData(bool has_unsaved_data);

    /**
     * @brief emitted when the source code was loaded from file.
     * @param new_source_code
     */
    void newSourceCodeLoaded(QString new_source_code);

    /**
     * @brief emitted when the history is loaded from file
     * @param history
     */
    void newHistoryLoaded(QVector<QString> history);
private:
    FileManager();

    void setCurrentFilePath(QString file_path);
    void setHasUnsavedData(bool has_unsaved_data);

    /**
     * @brief the full path to the file which is now opened.
     * Or empty string if the project was not saved.
     * NOTE: when the attribute is changed the fileNameChanged should be always emitted.
     * DIRECT EDIT IS FORBIDDEN use setCurrentFilePath
     */
    QString _current_file_path;

    /**
     * @brief true if there is anything unsaved.
     * When the attribute changed the hasUnsavedData should be emitted.
     * DIRECT EDIT IS FORBIDDEN use setHasUnsavedData
     */
    bool _has_unsaved_data;


    bool saveToFile(QString file_name);
};

#endif // FILEMANAGER_H
