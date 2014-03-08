#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T12:40:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_FILE = yad.rc

TARGET = "Yad Studio"
TEMPLATE = app
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Widgets

SOURCES += main.cpp\
        MainWindow.cpp \
    Widgets/MarkovWordWidget.cpp \
    Widgets/RunWidget.cpp \
    Widgets/DebugRunWidget.cpp \
    Widgets/InputWidget.cpp \
    Widgets/HistoryWidget.cpp \
    Widgets/LineInfoWidget.cpp \
    Widgets/MarkovEditorWidget.cpp \
    Widgets/EditorWindowWidget.cpp \
    Logic/CompilerError.cpp \
    Logic/MarkovRule.cpp \
    Logic/MarkovAlphabet.cpp \
    Logic/MarkovAlgorithm.cpp \
    Logic/YadFile.cpp \
    Logic/MarkovParser.cpp \
    Logic/RunError.cpp \
    Managers/SourceCodeManager.cpp \
    Managers/HistoryManager.cpp \
    Managers/FileManager.cpp \
    Managers/MarkovRunManager.cpp

HEADERS  += MainWindow.h \
    Widgets/MarkovWordWidget.h \
    Widgets/RunWidget.h \
    Widgets/DebugRunWidget.h \
    Widgets/InputWidget.h \
    Widgets/HistoryWidget.h \
    Widgets/LineInfoWidget.h \
    Widgets/MarkovEditorWidget.h \
    Widgets/EditorWindowWidget.h \
    Logic/CompilerError.h \
    Logic/MarkovRule.h \
    Logic/MarkovAlphabet.h \
    Logic/MarkovAlgorithm.h \
    Logic/YadFile.h \
    Logic/MarkovParser.h \
    Logic/RunError.h \
    Managers/SourceCodeManager.h \
    Managers/HistoryManager.h \
    Managers/FileManager.h \
    Managers/MarkovRunManager.h

FORMS    += MainWindow.ui \
    Widgets/MarkovWordWidget.ui \
    Widgets/RunWidget.ui \
    Widgets/DebugRunWidget.ui \
    Widgets/InputWidget.ui \
    Widgets/HistoryWidget.ui \
    Widgets/LineInfoWidget.ui \
    Widgets/EditorWindowWidget.ui

RESOURCES += \
    Resources.qrc
