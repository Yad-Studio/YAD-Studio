#ifndef EDITORWINDOWWIDGET_H
#define EDITORWINDOWWIDGET_H

#include <QWidget>

namespace Ui {
class EditorWindowWidget;
}

class EditorWindowWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EditorWindowWidget(QWidget *parent = 0);
    ~EditorWindowWidget();
    
private:
    Ui::EditorWindowWidget *ui;
};

#endif // EDITORWINDOWWIDGET_H
