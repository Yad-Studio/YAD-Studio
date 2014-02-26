#ifndef LINEINFOWIDGET_H
#define LINEINFOWIDGET_H

#include <QWidget>

namespace Ui {
class LineInfoWidget;
}

class LineInfoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LineInfoWidget(QWidget *parent = 0);
    ~LineInfoWidget();
    
private:
    Ui::LineInfoWidget *ui;
};

#endif // LINEINFOWIDGET_H
