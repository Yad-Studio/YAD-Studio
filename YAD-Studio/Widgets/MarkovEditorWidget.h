#ifndef MARKOVEDITORWIDGET_H
#define MARKOVEDITORWIDGET_H

#include <QTextEdit>


class MarkovEditorWidget : public QTextEdit
{
    Q_OBJECT
    
public:
    explicit MarkovEditorWidget(QWidget *parent = 0);
    ~MarkovEditorWidget();
    
private:

};

#endif // MARKOVEDITORWIDGET_H
