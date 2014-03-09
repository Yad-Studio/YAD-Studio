#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f=a.font();
//    f.setFamily("Segoe UI");
//    f.setStyleStrategy(QFont::PreferAntialias);
//    a.setFont(f);

    MainWindow w;
    w.show();
    
    return a.exec();
}
