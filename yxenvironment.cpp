#include "yxenvironment.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QSettings>
DectectFunction YXENVIRONMENT::detectFun = NULL;
QString YXENVIRONMENT::detectpath_gong = NULL;
QString YXENVIRONMENT::detectpath_mu = NULL;
QString YXENVIRONMENT::lightpath = NULL;
QString YXENVIRONMENT::configDataPath = NULL;
SysUser YXENVIRONMENT::currentuser = NULL;
YXENVIRONMENT::YXENVIRONMENT()
{

}
void YXENVIRONMENT::load()
{

    YXENVIRONMENT::loadlibs();
    YXENVIRONMENT::loadvariables();
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QSettings *settings = new QSettings("fiber.ini", QSettings::IniFormat);
    settings->setIniCodec(codec);
    settings->beginWriteArray("Templates");
    for (int i = 0; i < 5; ++i) {

        settings->setArrayIndex(i);
        settings->setValue("ID", QDateTime::currentDateTime().toString("TyyyyMMddhhmmss"));
        settings->setValue("Title", QString("线束1-%1").arg(i));
        settings->setValue("Model", "F12-R45");
        settings->setValue("TotalHoleCount", 34);
        settings->setValue("LocationHoleCount", 2);
        settings->setValue("Creator", "admin");
        settings->setValue("CreateDate", QDateTime::currentDateTime());
    }

    settings->endArray();
    delete settings;
}

void YXENVIRONMENT::loadlibs()
{
    QString apiPath = QDir::currentPath() + "/tmpApi.dll";
    if(QFile::exists(apiPath))
    {
        QFile::remove(apiPath);
    }
    QFile dllFile(":/libs/Both_Detect_DefectOrlight.dll");
    dllFile.copy(apiPath);
    QLibrary detectLibrary(apiPath);
    if(detectLibrary.load())
    {
        //?mutou_Detect_Defect@@YA_NPEAD0@Z
        YXENVIRONMENT::detectFun = (DectectFunction)detectLibrary.resolve("?Both_Detect_DefectOrlight@@YA_NPEAD000@Z");
        if ( detectFun )
        {
            qDebug() << "QLibrary resolve A!";
        }
        else
        {
            qDebug()<<detectLibrary.errorString()<<endl;
        }
    }
    else {
        qDebug() << "QLibrary load error A!";
        qDebug()<<detectLibrary.errorString()<<endl;
    }
}

void YXENVIRONMENT::loadvariables()
{
    YXENVIRONMENT::configDataPath = QDir::currentPath() + "/gpldata01.txt";
    YXENVIRONMENT::detectpath_gong = QDir::currentPath() + "/DetectDefect_gongtou.xml";
    YXENVIRONMENT::detectpath_mu = QDir::currentPath() + "/DetectDefect_mutou.xml";
    YXENVIRONMENT::lightpath = QDir::currentPath() + "/lightRank_gongtou.xml";

    qDebug()<<QDir::currentPath()<<endl;
    if(QFile::exists(configDataPath))
    {
        if(QFile::remove(configDataPath))
        {
            qDebug()<<"remove"<<configDataPath<<endl;
        }
    }

    if(QFile::exists(detectpath_gong))
    {
        QFile::remove(detectpath_gong);
    }

    if(QFile::exists(detectpath_mu))
    {
        QFile::remove(detectpath_mu);
    }
    if(QFile::exists(lightpath))
    {
        QFile::remove(lightpath);
    }

    QFile::copy(":/configs/gpldata01.txt", "gpldata01.txt");
    QFile foo("gpldata01.txt");
    foo.setPermissions(QFile::WriteUser);
}
