#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QMainWindow>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();
    
private:
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H
