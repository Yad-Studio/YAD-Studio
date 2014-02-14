#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->mainButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}
void MainWindow::onButtonClicked()
{
    ui->comboBox->addItem("Item Text");
}

MainWindow::~MainWindow()
{
    delete ui;
}
