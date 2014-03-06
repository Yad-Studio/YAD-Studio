#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    static MainWindow* getInstance();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *);
public slots:
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
     * @brief shows or hides redo button
     */
    void redoAvailable(bool);

    /**
     * @brief shows or hides undo button
     */
    void undoAvailable(bool);

    /**
     * @brief shows or hides copy, cut, delete selection buttons
     */
    void copyAvailable(bool);

signals:
    void undo();
    void redo();
    void selectAll();
    void copy();
    void paste();
    void cut();
    void deleteSelection();
    void newFile();
    void open();
    void save();
    void saveAs();

private:
    Ui::MainWindow *ui;
    bool _has_unsaved_data;
    QString _current_file;
    static MainWindow* _window;
    void updateWindowTitle();
private slots:
    void newHistoryLoaded(QVector<QString>);
};

#endif // MAINWINDOW_H
