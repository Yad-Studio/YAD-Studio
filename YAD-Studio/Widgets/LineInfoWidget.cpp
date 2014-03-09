#include "LineInfoWidget.h"
#include "ui_LineInfoWidget.h"

LineInfoWidget::LineInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineInfoWidget)
{
    ui->setupUi(this);

}

LineInfoWidget::~LineInfoWidget()
{
    delete ui;

}

void LineInfoWidget::lineWithErrorFocus(int line_number, CompilerError error){
    ui->line_number->setText("Line #"+QString::number(line_number));
    //ui->error_title->setStyleSheet("QLabel { color : red; }");
    //ui->error_title->setText(error.getErrorTitle());
    //if(ui->error_description->isHidden())
    //    ui->error_description->show();
    //ui->error_description->setStyleSheet("QLabel { color : red; }");
    ui->error_description->setText(tr("<font color=red><b>%1: %2</b><br>%3</font>")
                                   .arg(
                                       QString::number(error.getErrorNumber()))
                                   .arg(error.getErrorTitle())
                                   .arg(error.getErrorDescription()));
}

void LineInfoWidget::lineWithoutErrorFocus(int line_number){
    ui->line_number->setText("Line #"+QString::number(line_number));
    //ui->error_title->setStyleSheet("QLabel { color : black; }");
    //ui->line_number->setText("Line #"+QString::number(line_number));
    //if(!ui->error_description->isHidden())
    //    ui->error_description->hide();

    //ui->error_title->setAlignment(Qt::AlignVCenter);
    ui->error_description->setText("<font color=#a0a0a0>Line is correct</font>");
}
