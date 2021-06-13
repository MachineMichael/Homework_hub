#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QKeyEvent>
#include <QDebug>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(this, SIGNAL(setRead(int)), this, SLOT(switchRead(int)));
    connect(this, SIGNAL(saveTxt()), this, SLOT(saveAs()));
    connect(this, SIGNAL(openTxt()), this, SLOT(open()));
    connect(this, SIGNAL(chooseLang(int)), this, SLOT(switchLang(int)));


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
        QMessageBox::information(this, tr("О программе"), about);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    emit openTxt();
}


void MainWindow::on_pushButton_clicked()
{
    emit saveTxt();
}


void MainWindow::open()
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

void MainWindow::saveAs()
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

void MainWindow::create()
{

}

void MainWindow::quitProgram()
{
    qApp->quit();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if((event->key() == Qt::Key_O)&&(event->modifiers() == Qt::CTRL)) open();
    else if ((event->key() == Qt::Key_S)&&(event->modifiers() == Qt::CTRL)) saveAs();
    else if ((event->key() == Qt::Key_Q)&&(event->modifiers() == Qt::CTRL)) this->close();
    else if ((event->key() == Qt::Key_N)&&(event->modifiers() == Qt::CTRL)) {ui->plainTextEdit->clear(); open();}
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

void MainWindow::switchLang(int x) {

    qDebug() << x;

    switch (x) {

    case 0: break;
    case 1: {
        if(translator.load(":/tr/QtLanguage_eng.qm")) {
        qApp->installTranslator(&translator);
        }
        else qDebug() << "no success";
        break;
    }

    }


}

void MainWindow::switchRead(int a) {

    switch (a) {
    case 0: ui->plainTextEdit->setReadOnly(false);
        connect(this, SIGNAL(saveTxt()), this, SLOT(saveAs()));
        ui->pushButton->setEnabled(true);
        break;
    case 1: ui->plainTextEdit->setReadOnly(true);
        disconnect(this, SIGNAL(saveTxt()), this, SLOT(saveAs()));
        ui->pushButton->setEnabled(false);
        break;
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()) {

        emit setRead(1);
    }
    else if(!ui->checkBox->isChecked()) {

        emit setRead(0);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    emit chooseLang(0);
}


void MainWindow::on_pushButton_5_clicked()
{
    emit chooseLang(1);
}

void MainWindow::on_lineEdit_selectionChanged()
{
    if (ui->lineEdit->isActiveWindow()) {

    }
}

