#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <textspecialreplace.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list1 {"C++", "Python", "C#", "Java", "PHP", "JavaScript"};
    QStringList list2 {"1", "2", "3", "4"};
    QStringList headers {"Num", "Name", "IP", "MAC"};

    model = new QStandardItemModel(list2.size(), 1, this);
        for(int i = 0; i<model->rowCount(); i++) {
            QModelIndex index = model->index(i, 0);
            QString str = list2[i];
            model->setData(index, str, Qt::DisplayRole);
        }

    smodel = new QStandardItemModel(list1.size(), 1, this);
    for(int i = 0; i<smodel->rowCount(); i++) {
        QModelIndex index = smodel->index(i, 0);
        QString str = list1[i];
        smodel->setData(index, str, Qt::DisplayRole);
        smodel->setData(index, QIcon(".Icons/"+str+".png"), Qt::DecorationRole);
    }

    ui->listView->setModel(smodel);
    ui->listView->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);


    model->setHorizontalHeaderLabels(headers);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{

}


void MainWindow::on_pushButton_clicked()
{
    TextSpecialReplace txt(ui->plainTextEditSymbols->toPlainText());
    ui->plainTextEditSymbols->clear();
    ui->plainTextEditSymbols->appendPlainText(txt.txt);
}


void MainWindow::on_pushButton_2_clicked()
{
    QStandardItem *item = new QStandardItem();
    item->setData(QIcon(".Icons/Default.png"), Qt::DecorationRole);
    item->setData(ui->lineEdit->text(), Qt::DisplayRole);
    smodel->appendRow(item);
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()) ui->listView->setViewMode(QListView::IconMode);
    else ui->listView->setViewMode(QListView::ListMode);
}


void MainWindow::on_pushButton_3_clicked()
{
    int row = ui->listView->currentIndex().row();
    smodel->removeRow(row);
}


void MainWindow::on_pushButton_4_clicked()
{
    int row = ui->listView->currentIndex().row();
    smodel->moveRow(smodel->index(row, 0), row, smodel->index(row-1, 0), row-1);

}


void MainWindow::on_pushButton_5_clicked()
{
    int row = ui->listView->currentIndex().row();
    smodel->moveRow(smodel->index(row, 0), row, smodel->index(row+1, 0), row+1);
}


void MainWindow::on_pushButton_6_clicked()
{
    QPalette pal;
    pal.setColor(QPalette::Base, Qt::green);
    ui->tableView->setPalette(pal);
}

