#ifndef YXENVIRONMENT_H
#define YXENVIRONMENT_H
#include <QtWidgets>
#include <QLibrary>
#include "sysuser.h"
typedef bool (*DectectFunction)(char *,char *,char *,int);
class YXENVIRONMENT
{
public:
    explicit YXENVIRONMENT();
    static DectectFunction detectFunM;
    static DectectFunction detectFunF;

    static QString detectpath;
    static void load();

    static void setSkinStyles();
    static SysUser currentuser;
private:
    static void loadlibs();
    static void loadvariables();

};

#endif // YXENVIRONMENT_H
