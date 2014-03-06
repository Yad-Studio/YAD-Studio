#include "EditorWindowWidget.h"
#include "ui_EditorWindowWidget.h"
#include "MarkovEditorWidget.h"

EditorWindowWidget::EditorWindowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWindowWidget)
{
    ui->setupUi(this);

    connect(ui->plainTextEdit, SIGNAL(canRun(bool)),
            this, SIGNAL(canRun(bool)));
    connect(ui->plainTextEdit, SIGNAL(sourceCodeChanged(QString)),
            this, SIGNAL(sourceCodeChanged(QString)));
    connect(ui->plainTextEdit, SIGNAL(markovAlgorithmChanged(MarkovAlgorithm)),
            this, SIGNAL(markovAlgorithmChanged(MarkovAlgorithm)));
    connect(ui->plainTextEdit, SIGNAL(redoAvailable(bool)),
            this, SIGNAL(redoAvailable(bool)));
    connect(ui->plainTextEdit, SIGNAL(undoAvailable(bool)),
            this, SIGNAL(undoAvailable(bool)));
    connect(ui->plainTextEdit, SIGNAL(copyAvailable(bool)),
            this, SIGNAL(copyAvailable(bool)));
}

EditorWindowWidget::~EditorWindowWidget()
{
    delete ui;
}

void EditorWindowWidget::newSourceCode(QString new_source)
{
    ui->plainTextEdit->newSourceCode(new_source);
}

void EditorWindowWidget::undo()
{
    ui->plainTextEdit->undo();
}

void EditorWindowWidget::redo()
{
    ui->plainTextEdit->redo();
}
void EditorWindowWidget::selectAll()
{
    ui->plainTextEdit->selectAll();
}

void EditorWindowWidget::copy()
{
    ui->plainTextEdit->copy();
}
void EditorWindowWidget::paste()
{
    ui->plainTextEdit->paste();
}

void EditorWindowWidget::cut()
{
    ui->plainTextEdit->cut();
}
void EditorWindowWidget::deleteSelection()
{
    ui->plainTextEdit->deleteSelection();
}
