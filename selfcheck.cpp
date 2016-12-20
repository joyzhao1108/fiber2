#include "selfcheck.h"
#include "yxenvironment.h"
#include <QtWidgets>
//#define MB （1024 * 1024）
SelfCheck::SelfCheck(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("product name"));
    this->setWindowIcon(QIcon(":/icons/logo"));
    selfCheckTextEdit = new QTextEdit;

    selfCheckTextEdit->setObjectName("selfCheckTextEdit");
    selfCheckTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    /*exitButton = new QPushButton(tr("&Cancel"));
    connect(exitButton,&QPushButton::clicked, this, &QDialog::reject);
    QHBoxLayout *hxLayout = new QHBoxLayout;
    hxLayout->addStretch(0);
    hxLayout->addWidget(exitButton);*/
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(selfCheckTextEdit);
    //mainLayout->addSpacing(200);
    //mainLayout->addLayout(hxLayout);
    //mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
    //connect(this, &SelfCheck::windowLoaded, this, &SelfCheck::check, Qt::ConnectionType(Qt::QueuedConnection | Qt::UniqueConnection));
    //QApplication::processEvents();

    //QApplication::processEvents();
}
void SelfCheck::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    //emit windowLoaded();
    /*if( event->spontaneous() )
     return;
    if(isInitialized)
        return;

    // do your init stuff here
    emit windowLoaded();
    isInitialized = true;

*/
    return;
}
int SelfCheck::check()
{
    appendlog(tr("start checking..."));
    QThread::sleep(2);
    appendlog(tr("check system info..."));
//    SYSTEM_INFO systemInfo;
//    GetSystemInfo(&systemInfo);
//    QStringList syteminfolog;
//    syteminfolog << tr("Numbers of CPUs:") << systemInfo.dwNumberOfProcessors << " ";
//    syteminfolog << tr("CPU type:") << systemInfo.dwProcessorType << " ";
//    syteminfolog << tr("CPU Level:") << systemInfo.wProcessorLevel << " ";
//    syteminfolog << tr("CPU Version:") << systemInfo.wProcessorRevision << " ";
//    appendlog(syteminfolog.join(" "));
    QStringList environmentList = QProcess::systemEnvironment();
    foreach (QString environment, environmentList )
    {
        appendlog(environment);
    }
    /*MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    qDebug() << QStringLiteral("物理内存使用率:") << statex.dwMemoryLoad;
    qDebug() << QStringLiteral("物理内存总量:") << statex.ullTotalPhys/MB;
    qDebug() << QStringLiteral("可用的物理内存:") << statex.ullAvailPhys/MB;
    qDebug() << QStringLiteral("系统页面文件大小:") << statex.ullTotalPageFile/MB;
    qDebug() << QStringLiteral("系统可用页面文件大小:") << statex.ullAvailPageFile/MB;
    qDebug() << QStringLiteral("虚拟内存总量:") << statex.ullTotalVirtual/MB;
    qDebug() << QStringLiteral("可用的虚拟内存:") << statex.ullAvailVirtual/MB;
    qDebug() << QStringLiteral("保留（值为0）:") << statex.ullAvailExtendedVirtual/MB;*/
    QThread::sleep(3);
    appendlog(tr("check environment variables..."));
    YXENVIRONMENT::load();
    QThread::sleep(2);
    appendlog(tr("environment variables loaded!"));
    QThread::sleep(2);
    appendlog(tr("check camera..."));
    QThread::sleep(3);
    appendlog(tr("camera load and init successfully!"));
    QThread::sleep(2);
    appendlog(tr("Setting up the main window..."));
    QThread::sleep(3);
    appendlog(tr("start..."));
    QThread::sleep(1);
    return 1;
}

void SelfCheck::appendlog(const QString &text)
{
    QStringList log;
    log << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << text;
    selfCheckTextEdit->append(log.join(":"));
    //statuslogTextEdit->moveCursor(QTextCursor::Start) ;
    //statuslogTextEdit->ensureCursorVisible();
    selfCheckTextEdit->verticalScrollBar()->setValue(selfCheckTextEdit->verticalScrollBar()->maximum());
    QApplication::processEvents();
}
void SelfCheck::appenderror(const QString &text)
{
    appendlog(QString("<span style=' color:#ff0000;'>%1</span>").arg(text));
    QApplication::processEvents();
}
