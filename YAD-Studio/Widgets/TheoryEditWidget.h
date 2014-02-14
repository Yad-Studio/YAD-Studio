#ifndef THEORYEDITWIDGET_H
#define THEORYEDITWIDGET_H

#include <QWidget>

namespace Ui {
class TheoryEditWidget;
}

class TheoryEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TheoryEditWidget(QWidget *parent = 0);
    ~TheoryEditWidget();

private:
    Ui::TheoryEditWidget *ui;
};

#endif // THEORYEDITWIDGET_H
