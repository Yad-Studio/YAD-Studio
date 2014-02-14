#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MyModule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void myAction();

private:
    Ui::MainWindow *ui;
    MyModule _module;

private slots:
    void onButtonClicked();
};

#endif // MAINWINDOW_H
