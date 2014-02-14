#ifndef WORKINGPANEL_H
#define WORKINGPANEL_H

#include <QWidget>

namespace Ui {
class WorkingPanel;
}

class WorkingPanel : public QWidget
{
    Q_OBJECT

public:
    explicit WorkingPanel(QWidget *parent = 0);
    ~WorkingPanel();

private:
    Ui::WorkingPanel *ui;
};

#endif // WORKINGPANEL_H
