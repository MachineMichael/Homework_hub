#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QGridLayout>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea(this);
    QWidget *wgt = new QWidget(this);
    setCentralWidget(wgt);
    QGridLayout *layout = new QGridLayout(this);
    wgt->setLayout(layout);
    layout->addWidget(mdiArea, 0,0,10,1);

    QTextEdit* TextEdit1 = new QTextEdit(this);
    mdiArea->addSubWindow(TextEdit1);
    mdiArea->addSubWindow(new QTextEdit(this));
    mdiArea->setViewMode(QMdiArea::TabbedView);

    QMenu* fileMenu = menuBar()->addMenu(tr("Файл"));

    QAction* newTab = fileMenu->addAction(tr("Новая вкладка"));
    connect(newTab, SIGNAL(triggered()), this, SLOT(addNewTab()));
    QAction* deleteTab = fileMenu->addAction(tr("Удалить вкладку"));
    connect(deleteTab, SIGNAL(triggered()), this, SLOT(deleteCurrentTab()));

    QAction* print = fileMenu->addAction(tr("Печать"));
    connect(print, SIGNAL(triggered()), this, SLOT(sendToPrint()));

    QMenu* viewMenu = menuBar()->addMenu(tr("Вид"));

    QMenu* subLangMenu = new QMenu(tr("Язык:"));
    QAction* langRus = subLangMenu->addAction(tr("Русский"));
    QAction* langEng = subLangMenu->addAction(tr("Английский"));
    connect(langRus, SIGNAL(triggered()), this, SLOT(switchToRus()));
    connect(langEng, SIGNAL(triggered()), this, SLOT(switchToEng()));

    viewMenu->addMenu(subLangMenu);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewTab() {

   QMdiArea* mdi = this->mdiArea;
   QTextEdit* te = new QTextEdit(this);
   mdi->addSubWindow(te);
   te->show();


}

void MainWindow::deleteCurrentTab() {

    mdiArea->removeSubWindow((QWidget*) mdiArea->currentSubWindow());

}

void MainWindow::switchToRus() {

    if(translator->load(":/tr/QtLanguage_ru.qm")) {
    qApp->installTranslator(translator);
    //ui->retranslateUi(this);
    }

}

void MainWindow::switchToEng() {

    if(translator->load(":/tr/QtLanguage_en.qm")) {
    qApp->installTranslator(translator);
    //ui->retranslateUi(this);
    }

}

void MainWindow::sendToPrint() {

    QMdiSubWindow* active = this->mdiArea->activeSubWindow();
    QWidget* widget1 = active->widget();
    QTextEdit* textEdit = (QTextEdit*)widget1;
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle(tr("Печать"));
    if(dlg.exec() != QDialog::Accepted) return;
    textEdit->print(&printer);

}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

