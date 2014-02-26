#include "EditorWindowWidget.h"
#include "ui_EditorWindowWidget.h"

EditorWindowWidget::EditorWindowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWindowWidget)
{
    ui->setupUi(this);
}

EditorWindowWidget::~EditorWindowWidget()
{
    delete ui;
}
