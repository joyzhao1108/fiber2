#include "yxenvironment.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QSettings>
DectectFunction YXENVIRONMENT::detectFunM = NULL;
DectectFunction YXENVIRONMENT::detectFunF = NULL;
QString YXENVIRONMENT::detectpath = NULL;
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
    QString templatePath = QString("%1/template/%2/").arg(QDir::currentPath()).arg(1);

    QDir::current().mkpath(QString("%1/template/%2/").arg(QDir::currentPath()).arg(1));
    if(!settings->childGroups().contains("Templates"))
    {
        settings->beginWriteArray("Templates");

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
        settings->setValue("DivideHoleRadius", 79);
        settings->setValue("CirqueOutRadius", 32);
        settings->setValue("CirqueInRadius", 23);
        settings->setValue("GongHoughMinRadius", 510);
        settings->setValue("GongHoughMaxRadius", 530);
        settings->setValue("MuHoughMinRadius", 10);
        settings->setValue("MuHoughMaxRadius", 50);
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
        settings->setValue("ConfigDataPath", templatePath + "gpldata02.txt");
        settings->setValue("BasePicPath", templatePath + "female.bmp");
        settings->setValue("DivideHoleRadius", 79);
        settings->setValue("CirqueOutRadius", 32);
        settings->setValue("CirqueInRadius", 23);
        settings->setValue("GongHoughMinRadius", 510);
        settings->setValue("GongHoughMaxRadius", 530);
        settings->setValue("MuHoughMinRadius", 10);
        settings->setValue("MuHoughMaxRadius", 50);
        QPixmap(":/images/female-test.bmp").save(templatePath + "female.bmp");
        settings->endArray();
    }
    if(!settings->childGroups().contains("SysConfigs"))
    {
        settings->beginGroup("SysConfigs");
        settings->setValue("RadiusLimit", 1.5000000);
        settings->setValue("LightRankLowBound", 200);
        settings->endGroup();
    }
    delete settings;


    QFile::copy(":/configs/gpldata01.txt", templatePath + "gpldata01.txt");
    QFile foo(templatePath + "gpldata01.txt");
    foo.setPermissions(QFile::WriteUser);

    QFile::copy(":/configs/gpldata02.txt", templatePath + "gpldata02.txt");
    QFile foo2(templatePath + "gpldata02.txt");
    foo2.setPermissions(QFile::WriteUser);
}

void YXENVIRONMENT::loadlibs()
{
    QString apiPathM = QDir::currentPath() + "/tmpApiM.dll";
    if(QFile::exists(apiPathM))
    {
        QFile::remove(apiPathM);
    }
    QFile dllFileM(":/libs/gongtou_Detect_DefectOrlight.dll");
    dllFileM.copy(apiPathM);
    dllFileM.close();
    QLibrary detectLibraryM(apiPathM);
    if(detectLibraryM.load())
    {
        //?mutou_Detect_Defect@@YA_NPEAD0@Z
        YXENVIRONMENT::detectFunM = (DectectFunction)detectLibraryM.resolve("gongtou_Detect_DefectOrlight");
        if ( detectFunM )
        {
            qDebug() << "QLibrary resolve M!";
        }
        else
        {
            qDebug()<<detectLibraryM.errorString()<<endl;
        }
    }
    else {
        qDebug() << "QLibrary load error M!";
        qDebug()<<detectLibraryM.errorString()<<endl;
    }
    QString apiPathF = QDir::currentPath() + "/tmpApiF.dll";
    if(QFile::exists(apiPathF))
    {
        QFile::remove(apiPathF);
    }
    QFile dllFileF(":/libs/mutou_Detect_DefectOrlight.dll");
    dllFileF.copy(apiPathF);
    dllFileF.close();
    QLibrary detectLibraryF(apiPathF);
    if(detectLibraryF.load())
    {
        //?mutou_Detect_Defect@@YA_NPEAD0@Z
        YXENVIRONMENT::detectFunF = (DectectFunction)detectLibraryF.resolve("mutou_Detect_DefectOrlight");
        if ( detectFunF )
        {
            qDebug() << "QLibrary resolve F!";
        }
        else
        {
            qDebug()<<detectLibraryF.errorString()<<endl;
        }
    }
    else {
        qDebug() << "QLibrary load error F!";
        qDebug()<<detectLibraryF.errorString()<<endl;
    }
}

void YXENVIRONMENT::loadvariables()
{
    YXENVIRONMENT::detectpath = QDir::currentPath() + "/DetectResult.xml";

    if(QFile::exists(detectpath))
    {
        QFile::remove(detectpath);
    }
}

void YXENVIRONMENT::setSkinStyles()
{
    QFile skinFile(":/skins/default.qss");
    skinFile.open( QFile::ReadOnly | QFile::Unbuffered );
    qApp->setStyleSheet( skinFile.readAll( ) );
    skinFile.close( );
}
