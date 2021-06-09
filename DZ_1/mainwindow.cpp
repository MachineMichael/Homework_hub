#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    float a = ui->lineEditA->text().toFloat();
    float b = ui->lineEditB->text().toFloat();
    float c = ui->lineEditC->text().toFloat();

    if (a==0) {
        ui->textBrowserAnswer1->clear();
        ui->textBrowserAnswer1->append("Единственный корень: ");
        ui->textBrowserAnswer1->append(QString::number(-c/b));
    }

    else {

        float disc = (b*b - 4*a*c);

        if(disc<0) {
            ui->textBrowserAnswer1->clear();
            ui->textBrowserAnswer1->append("Нет корней");    }
        else if(disc==0) {
            float ans1 = (-b + sqrt(disc))/(2*a);
            ui->textBrowserAnswer1->clear();
            ui->textBrowserAnswer1->append("Единственный корень: ");
            ui->textBrowserAnswer1->append(QString::number(ans1));
        }
        else if(disc>0) {
            float ans1 = (-b + sqrt(disc))/(2*a);
            float ans2 = (-b - sqrt(disc))/(2*a);
            ui->textBrowserAnswer1->clear();
            ui->textBrowserAnswer1->append("Два корня: ");
            ui->textBrowserAnswer1->append(QString::number(ans1));
            ui->textBrowserAnswer1->append(" и ");
            ui->textBrowserAnswer1->append(QString::number(ans2));
        }
    }


}


void MainWindow::on_pushButton_2_clicked()
{
    float side1 = ui->lineEditSide1->text().toFloat();
    float side2 = ui->lineEditSide2->text().toFloat();
    float angle;

    if(ui->radioButtonRad->isChecked()) {
        angle = ui->lineEditAngle->text().toFloat();
    }
    else if(ui->radioButtonDeg->isChecked()) {
        angle = (ui->lineEditAngle->text().toFloat())*M_PI/180;
    }

    if(angle<0) {angle = -angle;}

    while(angle>M_PI) {angle = angle - M_PI;}

    float side3 = sqrt(side1*side1 + side2*side2 - 2*side1*side2*cos(angle));

    ui->textBrowserAnswer2->clear();
    ui->textBrowserAnswer2->append("Третья сторона = ");
    ui->textBrowserAnswer2->append(QString::number(side3));

}


void MainWindow::on_pushButton_3_clicked()
{
    ui->plainTextEdit2->appendPlainText(ui->plainTextEdit1->toPlainText());
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->plainTextEdit1->clear();
    ui->plainTextEdit1->appendPlainText(ui->plainTextEdit2->toPlainText());
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->plainTextEdit1->appendHtml("<font color='red'>Hello</font>");
    ui->plainTextEdit2->appendHtml("<font color='blue'>Hello</font>");
}

