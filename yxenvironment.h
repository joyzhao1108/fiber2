#ifndef YXENVIRONMENT_H
#define YXENVIRONMENT_H
#include <QtWidgets>
#include <QLibrary>
#include "sysuser.h"
typedef bool (*DectectFunction)(char *,char *,char *,char *);
class YXENVIRONMENT
{
public:
    explicit YXENVIRONMENT();
    static DectectFunction detectFun;

    static QString detectpath_gong;
    static QString detectpath_mu;
    static QString lightpath;
    static void load();

    static void setSkinStyles();
    static SysUser currentuser;
private:
    static void loadlibs();
    static void loadvariables();

};

#endif // YXENVIRONMENT_H
