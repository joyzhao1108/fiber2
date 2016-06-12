#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workmdi.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("product name"));
    setWindowIcon(QIcon(":/icons/logo.ico"));
    mdiArea = new QMdiArea(this);
    mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
    //mdiArea->showMaximized();

    setCentralWidget(mdiArea);

    //QBrush b=QBrush(QColor(30,30,30),Qt::FDiagPattern);
    //mdiArea->setBackground(b);
    mdiArea->setViewMode(QMdiArea::TabbedView);
    mdiArea->setTabPosition(QTabWidget::West);
    mdiArea->setTabsClosable(false);
    mdiArea->setTabsMovable(true);
    mdiArea->setTabShape(QTabWidget::Triangular);
    mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation, false);
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createNew()
{
    WorkMdi *mdiWin1=new WorkMdi;
    mdiWin1->setWindowTitle("new1");
    mdiWin1->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(mdiWin1);
    mdiWin1->showMaximized();
}

void MainWindow::createActions()
{
    createNewAction = new QAction(QIcon(":/icons/photo.png"), tr("&Create..."), this);
    createNewAction->setShortcuts(QKeySequence::New);
    createNewAction->setStatusTip(tr("Create New..."));
    connect(createNewAction, &QAction::triggered, this, &MainWindow::createNew);

    quitAction = new QAction(QIcon(":/icons/quit.png"),tr("&Quit..."), this);
    quitAction->setShortcuts(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit Application"));
    QObject::connect(quitAction, &QAction::triggered, &QApplication::quit);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(createNewAction);
    file->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);

    ui->mainToolBar->addAction(createNewAction);
    ui->mainToolBar->addAction(quitAction);


}
