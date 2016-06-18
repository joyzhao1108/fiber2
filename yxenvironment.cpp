#include "yxenvironment.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QSettings>
DectectFunction YXENVIRONMENT::detectFun = NULL;
QString YXENVIRONMENT::detectpath_gong = NULL;
QString YXENVIRONMENT::detectpath_mu = NULL;
QString YXENVIRONMENT::lightpath = NULL;
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
    QString templatePath = QString("%1/template/%2/").arg(QDir::currentPath()).arg(1);

    QDir::current().mkpath(QString("%1/template/%2/").arg(QDir::currentPath()).arg(1));

    settings->setArrayIndex(0);
    settings->setValue("ID", QDateTime::currentDateTime().toString("TyyyyMMddhhmmss"));
    settings->setValue("Title", QString("线束- %1 - 公头").arg(1));
    settings->setValue("Model", "F12-R45");
    settings->setValue("TotalHoleCount", 34);
    settings->setValue("LocationHoleCount", 2);
    settings->setValue("Creator", "admin");
    settings->setValue("CreateDate", QDateTime::currentDateTime());
    settings->setValue("IsGongTou", true);
    settings->setValue("ConfigDataPath", templatePath + "gpldata01.txt");
    settings->setValue("BasePicPath", templatePath + "male.png");
    QPixmap(":/images/male-test.png").save(templatePath + "male.png");

    settings->setArrayIndex(1);
    settings->setValue("ID", QDateTime::currentDateTime().toString("TyyyyMMddhhmmss"));
    settings->setValue("Title", QString("线束- %1 - 母头").arg(1));
    settings->setValue("Model", "F12-R45");
    settings->setValue("TotalHoleCount", 34);
    settings->setValue("LocationHoleCount", 2);
    settings->setValue("Creator", "admin");
    settings->setValue("CreateDate", QDateTime::currentDateTime());
    settings->setValue("IsGongTou", false);
    settings->setValue("ConfigDataPath", templatePath + "gpldata01.txt");
    settings->setValue("BasePicPath", templatePath + "female.bmp");
    QPixmap(":/images/female-test.bmp").save(templatePath + "female.bmp");
    settings->endArray();
    delete settings;

    QFile::copy(":/configs/gpldata01.txt", templatePath + "gpldata01.txt");
    QFile foo(templatePath + "gpldata01.txt");
    foo.setPermissions(QFile::WriteUser);
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
    YXENVIRONMENT::detectpath_gong = QDir::currentPath() + "/DetectDefect_gongtou.xml";
    YXENVIRONMENT::detectpath_mu = QDir::currentPath() + "/DetectDefect_mutou.xml";
    YXENVIRONMENT::lightpath = QDir::currentPath() + "/lightRank_gongtou.xml";

    qDebug()<<QDir::currentPath()<<endl;


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
}

void YXENVIRONMENT::setSkinStyles()
{
    QFile skinFile(":/skins/default.qss");
    skinFile.open( QFile::ReadOnly | QFile::Unbuffered );
    qApp->setStyleSheet( skinFile.readAll( ) );
    skinFile.close( );
}
