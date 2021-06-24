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
#include <QPushButton>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    translator = new QTranslator;

    mdiArea = new QMdiArea(this);
    QWidget *wgt = new QWidget(this);
    setCentralWidget(wgt);
    QGridLayout *layout = new QGridLayout(this);
    wgt->setLayout(layout);
    layout->addWidget(mdiArea, 0,0,10,1);

    QWidget* buttonBlock = new QWidget(this);
    QGridLayout* buttonLayout = new QGridLayout(this);
    buttonBlock->setLayout(buttonLayout);
    QPushButton* copyStyleButton = new QPushButton(tr("Копировать стиль") ,this);
    connect(copyStyleButton, SIGNAL(clicked()), this, SLOT(copyStyle()) );
    QPushButton* pasteStyleButton = new QPushButton(tr("Применить стиль"), this);
    connect(pasteStyleButton, SIGNAL(clicked()), this, SLOT(pasteStyle()) );
    QPushButton* leftAlignStyleButton = new QPushButton(tr("По левому краю"), this);
    connect(leftAlignStyleButton, SIGNAL(clicked()), this, SLOT(pasteStyle()) );
    QPushButton* rightAlignStyleButton = new QPushButton(tr("По правому краю"), this);
    connect(rightAlignStyleButton, SIGNAL(clicked()), this, SLOT(pasteStyle()) );
    QPushButton* centerAlignStyleButton = new QPushButton(tr("По центру"), this);
    connect(centerAlignStyleButton, SIGNAL(clicked()), this, SLOT(pasteStyle()) );
    QPushButton* fontStyleButton = new QPushButton(tr("Установить шрифт"), this);
    connect(fontStyleButton, SIGNAL(clicked()), this, SLOT(fontStyle()) );
    buttonLayout->addWidget(copyStyleButton, 0,0,1,1);
    buttonLayout->addWidget(pasteStyleButton, 0,1,1,1);
    buttonLayout->addWidget(fontStyleButton, 0, 2, 1, 1);
    buttonLayout->addWidget(leftAlignStyleButton, 1,0,1,1);
    buttonLayout->addWidget(rightAlignStyleButton, 1,1,1,1);
    buttonLayout->addWidget(centerAlignStyleButton, 1,2,1,1);

    layout->addWidget(buttonBlock, 11, 0 , 2, 1);

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

    if(translator->load(":/tr/QtLanguage_ru.qm")) {
    qApp->installTranslator(translator);
    ui->retranslateUi(this);
    }


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

void MainWindow::copyStyle()
{
    QTextEdit* te = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    fmt = te->textCursor().charFormat();
}

void MainWindow::pasteStyle()
{
    QTextEdit* te = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    te->textCursor().setCharFormat(fmt);
}

void MainWindow::leftAlign()
{
    QTextEdit* te = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    te->setAlignment(Qt::AlignLeft);
//    QTextCursor cursor = te->textCursor();
//    QTextBlockFormat textBlockFormat = cursor.blockFormat();
//    textBlockFormat.setAlignment(Qt::AlignLeft);
//    cursor.mergeBlockFormat(textBlockFormat);
//    te->setTextCursor(cursor);
}

void MainWindow::rightAlign()
{
    QTextEdit* te = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    te->setAlignment(Qt::AlignRight);
//    QTextCursor cursor = te->textCursor();
//    QTextBlockFormat textBlockFormat = cursor.blockFormat();
//    textBlockFormat.setAlignment(Qt::AlignRight);
//    cursor.mergeBlockFormat(textBlockFormat);
//    te->setTextCursor(cursor);
}

void MainWindow::centerAlign()
{
    QTextEdit* te = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    te->setAlignment(Qt::AlignCenter);
//    QTextCursor cursor = te->textCursor();
//    QTextBlockFormat textBlockFormat = cursor.blockFormat();
//    textBlockFormat.setAlignment(Qt::AlignCenter);
//    cursor.mergeBlockFormat(textBlockFormat);
//    te->setTextCursor(cursor);
}

void MainWindow::fontStyle()
{
    QTextEdit* te = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = te->textCursor().charFormat().font();
    QFontDialog fntDlg(font, this);

    bool b[] = {true};
    font = fntDlg.getFont(b);
    if(b[0]) {
        QTextCharFormat fmt = te->textCursor().charFormat();
        fmt.setFont(font);
        te->textCursor().setCharFormat(fmt);
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

