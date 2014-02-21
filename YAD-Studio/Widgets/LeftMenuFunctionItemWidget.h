#ifndef LEFTMENUFUNCTIONITEMWIDGET_H
#define LEFTMENUFUNCTIONITEMWIDGET_H

#include <QWidget>

namespace Ui {
class LeftMenuFunctionItemWidget;
}
#include <QListWidgetItem>
class LeftMenuFunctionItemWidget : public QWidget
{
    Q_OBJECT
signals:
    // define mouseClick signal
    void onFocus();
public:
    void setName(const QString name);
    void setComment(const QString comment);
    explicit LeftMenuFunctionItemWidget(QWidget *parent = 0);
    ~LeftMenuFunctionItemWidget();

protected:
    // re-implement processing of mouse events
    void mouseReleaseEvent ( QMouseEvent * e );
    void mousePressEvent ( QMouseEvent * e );

private:
    Ui::LeftMenuFunctionItemWidget *ui;
    // member variable to store click position
    QPoint _m_lastPoint;
    // member variable - flag of click beginning
    bool _m_mouseClick;
};

#endif // LEFTMENUFUNCTIONITEMWIDGET_H
