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
    connect(this, SIGNAL(chooseStyle(int)), this, SLOT(switchStyle(int)));

    switchStyle(0);

//    model = new QFileSystemModel(this);
//    model->setRootPath(QDir::rootPath());
//    model->setReadOnly(false);


    fileBrowser = new FileBrowser(this);
    fileBrowser->setGeometry(590, 60, 271, 511);

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
    else if ((event->key() == Qt::Key_S)&&(event->modifiers() == Qt::CTRL)) emit saveTxt();
    else if ((event->key() == Qt::Key_Q)&&(event->modifiers() == Qt::CTRL)) this->close();
    else if ((event->key() == Qt::Key_N)&&(event->modifiers() == Qt::CTRL)) {ui->plainTextEdit->clear(); open();}
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
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

    case 0: {
        if(translator.load(":/tr/QtLanguage_ru.qm")) {
        qApp->installTranslator(&translator);
        }
        else qDebug() << "no success";
        break;
        break;
    }
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

void MainWindow::switchStyle(int a)
{
    if(a==0) {
        setStyleSheet("QMainWindow { background-color: #DBE7EA; color: #E85C09; }"
                    "QPushButton { background-color: #BAE7EA; color: #E85C09; font-size: 12px; }"
                    "QPushButton:pressed { background-color: #81A1A3; }"
                    "QPlainTextEdit { background-color: #F2F8FF; }"
                    "QLabel { color: #E85C09; } "
                    "QCheckBox { color: #E85C09; } "
                        );
    }
    else if(a==1) {
        setStyleSheet("QMainWindow { background-color: #245787;}"
                        "QPushButton { background-color: #3175B5; color: yellow; font-size: 12px }"
                        "QPushButton:pressed { background-color: #3B546E; }"
                        "QPlainTextEdit { background-color: #0D0159; }"
                    "QLabel { color: yellow; } "
                    "QCheckBox { color: yellow; } "
                        );
    }
}



void MainWindow::on_pushButton_7_clicked()
{
    emit chooseStyle(0);
}

void MainWindow::on_pushButton_6_clicked()
{
    emit chooseStyle(1);
}

