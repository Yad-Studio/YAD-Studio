#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _module()
{
    ui->setupUi(this);


}
void MainWindow::onButtonClicked()
{
}

MainWindow::~MainWindow()
{
    delete ui;
}
