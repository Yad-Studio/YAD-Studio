#ifndef DEBUGRUNWIDGET_H
#define DEBUGRUNWIDGET_H

#include <QWidget>

namespace Ui {
class DebugRunWidget;
}

class DebugRunWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DebugRunWidget(QWidget *parent = 0);
    ~DebugRunWidget();
    
private:
    Ui::DebugRunWidget *ui;
};

#endif // DEBUGRUNWIDGET_H
