#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>


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


void MainWindow::on_pushButton_3_clicked()
{
    QFile file(":/info/about.txt");
    if (file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        QString about(ba);
        QMessageBox::information(this, "О программе", about);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (path.isEmpty()) return;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        QString text(ba);
        ui->plainTextEdit->setPlainText(text);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getSaveFileName();
    if (path.isEmpty()) return;
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)){
        QString text = ui->plainTextEdit->toPlainText();
        QByteArray ba = text.toUtf8();
        file.write(ba, ba.length());
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QString html;
    QString path = QFileDialog::getOpenFileName(this, "Выберите html файл", "./", tr("*.html"));
    if (path.isEmpty()) return;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        html = ba;
        ui->plainTextEdit_2->setPlainText(html);
    }


    QStringList data = getData(html);

    ui->lineEditTemp->clear();
    ui->lineEditWeather->clear();
    ui->lineEditUSD->clear();
    ui->lineEditEUR->clear();

    ui->lineEditTemp->setText(data[0]);
    ui->lineEditWeather->setText(data[1]);
    ui->lineEditUSD->setText(data[2]);
    ui->lineEditEUR->setText(data[3]);


}

/*QString MainWindow::getHtml(const QString &url){
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    response->deleteLater();
    return response->readAll();
}*/

QStringList MainWindow::getData(const QString &html){

    QStringList list;
    int pos1 = 0, pos2 = 0;
    pos1 = html.indexOf("\"now\": {\"temp\": \"");
    if(pos1==-1) list.append("error");
    else {
            pos2 = html.indexOf("\"", pos1+17);
            list.append(html.mid(pos1+17, pos2-pos1-17));
        }

    pos1 = html.indexOf("\"description\": \"", pos2);
    if(pos1==-1) list.append("error");
    else {
            pos2 = html.indexOf("\"", pos1+16);
            list.append(html.mid(pos1+16, pos2-pos1-16));
    }

    pos1 = html.indexOf("\"USD\", \"rate\": ", pos2);
    if(pos1==-1) list.append("error");
    else {
        pos2 = html.indexOf(",", pos1+15);
        list.append(html.mid(pos1+15, pos2-pos1-15));
    }

    pos1 = html.indexOf("\"EUR\", \"rate\": ", pos2);
    if(pos1==-1) list.append("error");
    else {
            pos2 = html.indexOf(",", pos1+15);
            list.append(html.mid(pos1+15, pos2-pos1-15));
    }

    return list;
}

