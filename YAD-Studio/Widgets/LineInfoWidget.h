#ifndef LINEINFOWIDGET_H
#define LINEINFOWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

#include "Logic/CompilerError.h"
namespace Ui {
class LineInfoWidget;
}

class LineInfoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LineInfoWidget(QWidget *parent = 0);
    ~LineInfoWidget();
public slots:
    // display line number and error
    void lineWithErrorFocus(int line_number, CompilerError error);

    //selected line do not have error - DO NOT show LineInfoWidget in this case
    void lineWithoutErrorFocus(int line_number);
    
private:
    Ui::LineInfoWidget *ui;
protected:
    void paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
};

#endif // LINEINFOWIDGET_H
