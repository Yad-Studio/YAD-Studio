#include "FileManager.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QCoreApplication>
#include <QProcess>
#include <exception>
#include <QVector>
#include "Logic/YadFile.h"
#include "Managers/HistoryManager.h"
#include "Managers/SourceCodeManager.h"

#include "MainWindow.h"
FileManager* FileManager::getInstance()
{
    static FileManager* instance = nullptr;
    if(instance == nullptr)
        instance = new FileManager;
    return instance;
}

bool FileManager::hasUnsavedData()
{
    return _has_unsaved_data;
}

void FileManager::openFile(QString file_name)
{
    try
    {
        YadFile file = YadFile::readFromFile(file_name);

        setCurrentFilePath(file_name);
        emit newSourceCodeLoaded(file.getSourceCode());
        emit newHistoryLoaded(file.getHistory());

        setHasUnsavedData(false);
    }
    catch(std::exception e)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("<b>Can't open file %1</b>").arg(file_name));
        msgBox.setInformativeText(e.what());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

void FileManager::open()
{
    QString file_name = QFileDialog::getOpenFileName(MainWindow::getInstance(),
                                                    tr("Open File"),
                                                    "",
                                                    tr("Yad File (*.yad)"));
    if(file_name.size() > 0)
    {
        openFile(file_name);
    }
}

bool FileManager::save()
{
    if(_current_file_path.size() == 0)
    {
        return saveAs();
    }
    else
    {
        return saveToFile(_current_file_path);
    }
}

bool FileManager::saveAs()
{
    QString file_name = QFileDialog::getSaveFileName(
                MainWindow::getInstance(),
                tr("Save As"),
                "",
                tr("Yad File (*.yad)"));

    if(file_name.size() > 0)
    {
        return saveToFile(file_name);
    }
    return false;
}

void FileManager::newFile()
{
    QString current_exe = QCoreApplication::applicationFilePath();
    QProcess process;
    process.startDetached(current_exe);
}

bool FileManager::saveToFile(QString file_name)
{
    QString source_code = SourceCodeManager::getInstance()->getSourceCode();
    QVector<QString> history = HistoryManager::getInstance()->getHistory();

    YadFile file(source_code, history);

    try
    {
        file.saveToFile(file_name);
        setCurrentFilePath(file_name);
        setHasUnsavedData(false);
        return true;
    }
    catch(std::exception e)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("<b>Can't save file %1</b>").arg(file_name));
        msgBox.setInformativeText(e.what());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    return false;
}

void FileManager::sourceCodeChanged()
{
    setHasUnsavedData(true);
}

void FileManager::historyChanged()
{
    setHasUnsavedData(true);
}

FileManager::FileManager()
    : _has_unsaved_data(true),
      _current_file_path("")
{
}

void FileManager::setCurrentFilePath(QString file_path)
{
    if(_current_file_path != file_path)
    {
        _current_file_path = file_path;
        emit fileNameChanged(_current_file_path);
    }
}

void FileManager::setHasUnsavedData(bool has_unsaved_data)
{
    if(_has_unsaved_data != has_unsaved_data)
    {
        _has_unsaved_data = has_unsaved_data;
        emit hasUnsavedData(_has_unsaved_data);
    }
}
