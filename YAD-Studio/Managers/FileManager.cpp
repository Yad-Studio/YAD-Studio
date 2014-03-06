#include "FileManager.h"


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

}

void FileManager::open()
{

}

void FileManager::save()
{

}

void FileManager::saveAs()
{

}

void FileManager::newFile()
{

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
