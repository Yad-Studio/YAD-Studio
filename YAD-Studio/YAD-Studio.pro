#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T12:40:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YAD-Studio
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MyModule.cpp \
    Widgets/LeftMenuWidget.cpp \
    Widgets/WorkingPanel.cpp \
    Widgets/FunctionInfoWidget.cpp \
    Widgets/GUIEditWidget.cpp \
    Widgets/TextEditWidget.cpp \
    Widgets/TheoryEditWidget.cpp

HEADERS  += MainWindow.h \
    MyModule.h \
    Widgets/LeftMenuWidget.h \
    Widgets/WorkingPanel.h \
    Widgets/FunctionInfoWidget.h \
    Widgets/GUIEditWidget.h \
    Widgets/TextEditWidget.h \
    Widgets/TheoryEditWidget.h

FORMS    += MainWindow.ui \
    Widgets/LeftMenuWidget.ui \
    Widgets/WorkingPanel.ui \
    Widgets/FunctionInfoWidget.ui \
    Widgets/GUIEditWidget.ui \
    Widgets/TextEditWidget.ui \
    Widgets/TheoryEditWidget.ui
