#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T12:40:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YAD-Studio
TEMPLATE = app
INCLUDEPATH += $$PWD

SOURCES += main.cpp\
        MainWindow.cpp \
    MyModule.cpp \
    Widgets/LeftMenuWidget.cpp \
    Widgets/WorkingPanel.cpp \
    Widgets/FunctionInfoWidget.cpp \
    Widgets/GUIEditWidget.cpp \
    Widgets/TextEditWidget.cpp \
    Widgets/TheoryEditWidget.cpp \
    Logic/FunctionsStorage.cpp \
    Logic/Function.cpp \
    Logic/Term.cpp \
    Widgets/TermWidget.cpp \
    Widgets/LeftMenuFunctionItemWidget.cpp \
    Widgets/FunctionsListModel.cpp

HEADERS  += MainWindow.h \
    MyModule.h \
    Widgets/LeftMenuWidget.h \
    Widgets/WorkingPanel.h \
    Widgets/FunctionInfoWidget.h \
    Widgets/GUIEditWidget.h \
    Widgets/TextEditWidget.h \
    Widgets/TheoryEditWidget.h \
    Logic/FunctionsStorage.h \
    Logic/Function.h \
    Logic/Term.h \
    Widgets/TermWidget.h \
    Widgets/LeftMenuFunctionItemWidget.h \
    Widgets/FunctionsListModel.h

FORMS    += MainWindow.ui \
    Widgets/LeftMenuWidget.ui \
    Widgets/WorkingPanel.ui \
    Widgets/FunctionInfoWidget.ui \
    Widgets/GUIEditWidget.ui \
    Widgets/TextEditWidget.ui \
    Widgets/TheoryEditWidget.ui \
    Widgets/TermWidget.ui \
    Widgets/LeftMenuFunctionItemWidget.ui
