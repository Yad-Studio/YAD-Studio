#ifndef TEXTEDITWIDGET_H
#define TEXTEDITWIDGET_H

#include <QWidget>

namespace Ui {
class TextEditWidget;
}

class TextEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditWidget(QWidget *parent = 0);
    ~TextEditWidget();

private:
    Ui::TextEditWidget *ui;
};

#endif // TEXTEDITWIDGET_H
