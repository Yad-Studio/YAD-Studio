#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Logic/FunctionsStorage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _module()
{
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(hide()));

    FunctionPtr addition = Function::create();
    addition->setFunctionName("plus");
    addition->setArgumentsNumber(2);
    addition->setType(Function::Type::Recursive);
    addition->setArgumentName(0, "x");
    addition->setArgumentName(1, "y");

    FunctionsStorage::getInstance()->addFunction(addition);

    //=x
    TermPtr base = Term::create(Term::Type::Variable);
    base->setVariableIndex(0);

    //=S(?)
    TermPtr step = Term::create(Term::Type::Function);
    step->setFunctionID(FunctionsStorage::S);

    //=plus(x,y)
    TermPtr plus = Term::create(Term::Type::Function);
    plus->setFunctionID(addition->getID());

    TermPtr x = Term::create(Term::Type::Variable);
    x->setVariableIndex(0);

    TermPtr y = Term::create(Term::Type::Variable);
    y->setVariableIndex(1);

    plus->setTerm(0, x);
    plus->setTerm(1, y);

    step->setTerm(0, plus);

    addition->setRecursionBaseTerm(base);
    addition->setMainTerm(step);

    ui->workingPanel->onFunctionActive(addition);

}
void MainWindow::onButtonClicked()
{
}

MainWindow::~MainWindow()
{
    delete ui;
}
