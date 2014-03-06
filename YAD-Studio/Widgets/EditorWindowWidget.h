#ifndef EDITORWINDOWWIDGET_H
#define EDITORWINDOWWIDGET_H

#include <QWidget>
#include "Logic/MarkovAlgorithm.h"

namespace Ui {
class EditorWindowWidget;
}

class EditorWindowWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EditorWindowWidget(QWidget *parent = 0);
    ~EditorWindowWidget();
public slots:
    void newSourceCode(QString new_source);
    void undo();
    void redo();
    void selectAll();
    void copy();
    void paste();
    void cut();
    void deleteSelection();

signals:
    void canRun(bool);
    void sourceCodeChanged(QString);
    void markovAlgorithmChanged(MarkovAlgorithm);
    void redoAvailable(bool);
    void undoAvailable(bool);
    void copyAvailable(bool);

private:
    Ui::EditorWindowWidget *ui;
};

#endif // EDITORWINDOWWIDGET_H
