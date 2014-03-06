#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTextCursor>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

#include "Widgets/InputWidget.h"
#include "Widgets/HistoryWidget.h"
#include "Managers/HistoryManager.h"
#include "Managers/FileManager.h"
#include "Managers/MarkovRunManager.h"
#include "Managers/SourceCodeManager.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _has_unsaved_data(true),
    _current_file("")
{
    ui->setupUi(this);

    updateWindowTitle();
    redoAvailable(false);
    undoAvailable(false);
    copyAvailable(false);

    //Connect MainWindow menu
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SIGNAL(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), this, SIGNAL(redo()));
    connect(ui->actionSelect_All, SIGNAL(triggered()), this, SIGNAL(selectAll()));
    connect(ui->actionCopy, SIGNAL(triggered()), this, SIGNAL(copy()));
    connect(ui->actionPaste, SIGNAL(triggered()), this, SIGNAL(paste()));
    connect(ui->actionCut, SIGNAL(triggered()), this, SIGNAL(cut()));
    connect(ui->actionDelete, SIGNAL(triggered()), this, SIGNAL(deleteSelection()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SIGNAL(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SIGNAL(open()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SIGNAL(save()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SIGNAL(saveAs()));

    //Connect InputWidget and HistoryManager
    HistoryManager* history_manager = HistoryManager::getInstance();

    connect(ui->input, SIGNAL(addToHistory(QString)),
            history_manager, SLOT(addToHistory(QString)));
    connect(history_manager, SIGNAL(wordSelected(QString)),
            ui->input, SLOT(setInput(QString)));

    //Connect HistoryWidget and HistoryManager
    connect(ui->history, SIGNAL(inputWordSelected(QString)),
            history_manager, SIGNAL(wordSelected(QString)));
    connect(ui->history, SIGNAL(removeFromHistory(QString)),
            history_manager, SLOT(removeFromHistory(QString)));
    connect(history_manager, SIGNAL(historyChanged(QVector<QString>)),
            ui->history, SLOT(historyChanged(QVector<QString>)));

    //Connect MainWindows and FileManager
    FileManager* file_manager = FileManager::getInstance();
    connect(this, SIGNAL(newFile()), file_manager, SLOT(newFile()));
    connect(this, SIGNAL(open()), file_manager, SLOT(open()));
    connect(this, SIGNAL(save()), file_manager, SLOT(save()));
    connect(this, SIGNAL(saveAs()), file_manager, SLOT(saveAs()));
    connect(file_manager, SIGNAL(hasUnsavedData(bool)),
            this, SLOT(hasUnsavedData(bool)));
    connect(file_manager, SIGNAL(fileNameChanged(QString)),
            this, SLOT(fileNameChanged(QString)));

    //Connect MainWindows and EditorWindowWidget
    connect(this, SIGNAL(undo()), ui->editorWindow, SLOT(undo()));
    connect(this, SIGNAL(redo()), ui->editorWindow, SLOT(redo()));
    connect(this, SIGNAL(selectAll()), ui->editorWindow, SLOT(selectAll()));
    connect(this, SIGNAL(copy()), ui->editorWindow, SLOT(copy()));
    connect(this, SIGNAL(paste()), ui->editorWindow, SLOT(paste()));
    connect(this, SIGNAL(cut()), ui->editorWindow, SLOT(cut()));
    connect(this, SIGNAL(deleteSelection()),
            ui->editorWindow, SLOT(deleteSelection()));

    connect(ui->editorWindow, SIGNAL(redoAvailable(bool)),
            this, SLOT(redoAvailable(bool)));
    connect(ui->editorWindow, SIGNAL(undoAvailable(bool)),
            this, SLOT(undoAvailable(bool)));
    connect(ui->editorWindow, SIGNAL(copyAvailable(bool)),
            this, SLOT(copyAvailable(bool)));

    //Connect InputWidget and MarkovRunManager
    MarkovRunManager* run_manager = MarkovRunManager::getInstance();

    connect(ui->input, SIGNAL(run(QString)),
            run_manager, SLOT(runWithoutDebug(QString)));
    connect(ui->input, SIGNAL(runWithDebug(QString)),
            run_manager, SLOT(runWithDebug(QString)));
    connect(run_manager, SIGNAL(runWithoutDebugStarted(QString)),
            ui->input, SLOT(runStarted()));
    connect(run_manager, SIGNAL(debugStarted(QString)),
            ui->input, SLOT(runStarted()));
    connect(run_manager, SIGNAL(runWithoutDebugFinishFail(QString,RunError,int)),
            ui->input, SLOT(runFinished()));
    connect(run_manager, SIGNAL(runWithoutDebugFinishSuccess(QString,QString,int)),
            ui->input, SLOT(runFinished()));
    connect(run_manager, SIGNAL(debugFinishFail(QString,RunError,int)),
            ui->input, SLOT(runFinished()));
    connect(run_manager, SIGNAL(debugFinishSuccess(QString,QString,int)),
            ui->input, SLOT(runFinished()));
    connect(run_manager, SIGNAL(canRunSourceCode(bool)),
            ui->input, SLOT(canRunAlgorithm(bool)));

    //Connect SourceCodeManager and EditorWindowWidget
    SourceCodeManager* source_manager = SourceCodeManager::getInstance();
    connect(source_manager, SIGNAL(newSourceCodeWasLoaded(QString)),
            ui->editorWindow, SLOT(newSourceCode(QString)));
    connect(ui->editorWindow, SIGNAL(sourceCodeChanged(QString)),
            source_manager, SLOT(setSourceCode(QString)));

    //Read file to open from command line
    QStringList arguments = QCoreApplication::arguments();
    if(arguments.size() >= 2)
    {
        QString file_name = arguments.at(1);
        FileManager::getInstance()->openFile(file_name);
    }
    else
    {
        source_manager->setNewSourceCodeFromFile(tr("//Alphabet\nT = {}\n\n//Rules\n//a -> b"));
    }

}

void MainWindow::updateWindowTitle()
{
    QString file = _current_file;
    if(file == "")
        file = tr("Untitiled");

    QFileInfo fileInfo(file);
    QString filename(fileInfo.fileName());

    QString saved="";
    if(_has_unsaved_data)
        saved = "*";

    QString title = tr("%1%2 - Yad Studio").arg(filename, saved);
    this->setWindowTitle(title);
}

void MainWindow::fileNameChanged(QString new_name)
{
    _current_file = new_name;
    updateWindowTitle();
}

void MainWindow::hasUnsavedData(bool has_unsaved_data)
{
    _has_unsaved_data = has_unsaved_data;
    updateWindowTitle();
}

void MainWindow::redoAvailable(bool v)
{
    ui->actionRedo->setEnabled(v);
}

void MainWindow::undoAvailable(bool v)
{
    ui->actionUndo->setEnabled(v);
}

void MainWindow::copyAvailable(bool v)
{
    ui->actionCopy->setEnabled(v);
    ui->actionCut->setEnabled(v);
    ui->actionDelete->setEnabled(v);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if(FileManager::getInstance()->hasUnsavedData())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("<b>The document has been modified.</b>"));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        if(ret == QMessageBox::Save)
        {
            FileManager::getInstance()->save();
            QMainWindow::closeEvent(event);
        }
        else if(ret == QMessageBox::Discard)
        {
            QMainWindow::closeEvent(event);
        }
        else
        {
            event->ignore();
        }

    }
    else
    {
        QMainWindow::closeEvent(event);
    }
}
