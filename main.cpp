#include<TCHAR.h>
#include "initdialog.h"
#include "mainwindow.h"
#include "yxenvironment.h"
#include <QApplication>
#include <QTextCodec>
#include <Windows.h>
#include <DbgHelp.h>
#include "adminsettingdialog.h"
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{

//    HANDLE hDumpFile = CreateFile(TEXT("C:\\Test.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    if( hDumpFile != INVALID_HANDLE_VALUE){

//        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
//        dumpInfo.ExceptionPointers = pException;
//        dumpInfo.ThreadId = GetCurrentThreadId();
//        dumpInfo.ClientPointers = TRUE;

//        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
//    }
    //CreateDumpFile(TEXT("C:\\Test.dmp"), pException);
    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode,16)),errAdr(QString::number((uint)record->ExceptionAddress,16)),errMod;
    QMessageBox::critical(NULL,"application crashed","<FONT size=4><div><b>we feel very sorry for this error</b><br/></div>"+
                          QString("<div>errorcode%1</div><div>errorads%2</div></FONT>").arg(errCode).arg(errAdr),
                          QMessageBox::Ok);
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //DeclareDumpFile();
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    //    qDebug()<<"current applicationDirPath: "<<QCoreApplication::applicationDirPath();
    //    qDebug()<<"current currentPath: "<<QDir::currentPath();
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/loading.png"));
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),topRight, Qt::white);

    QTranslator qtranslator;
    if (qtranslator.load("fiber2", ":/lang")) {
        a.installTranslator(&qtranslator);
        qDebug() << "translate install sucess!";
    }

    splash->showMessage(QObject::tr("Loading modules..."),
                        topRight, Qt::white);
    //loadModules();
    YXENVIRONMENT::load();
    splash->showMessage(QObject::tr("Establishing connections..."),
                        topRight, Qt::white);
    //establishConnections();


    InitDialog initDlg;
    //initDlg->setAttribute(Qt::WA_DeleteOnClose);
    initDlg.setWindowFlags(Qt::WindowTitleHint);
    splash->finish(0);
    delete splash;
    int r = initDlg.exec();

    if(r == 7)
    {
        AdminSettingDialog adminDlg;
        adminDlg.show();
        return a.exec();
    }
    else if(r == 8)
    {
        MainWindow mainwin;
        mainwin.showMaximized();
        return a.exec();
    }
    else
    {
        return 0;
    }


}
