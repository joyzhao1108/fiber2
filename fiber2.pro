#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T20:34:59
#
#-------------------------------------------------

QT       += core gui xml axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fiber2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workmdi.cpp \
    yxenvironment.cpp \
    logindialog.cpp \
    initdialog.cpp \
    resultview.cpp \
    harnessconfigmodel.cpp \
    adminsettingdialog.cpp \
    adminsettingpage.cpp \
    defectresultmodel.cpp \
    sysuser.cpp \
    usermanagedialog.cpp \
    templatemodel.cpp \
    Camera_c.cpp \
    workmainwindow.cpp \
    reportview.cpp \
    selfcheck.cpp

HEADERS  += mainwindow.h \
    workmdi.h \
    yxenvironment.h \
    logindialog.h \
    initdialog.h \
    resultview.h \
    harnessconfigmodel.h \
    adminsettingdialog.h \
    adminsettingpage.h \
    defectresultmodel.h \
    sysuser.h \
    usermanagedialog.h \
    templatemodel.h \
    Camera_h.h \
    workmainwindow.h \
    reportview.h \
    selfcheck.h

FORMS    += mainwindow.ui

RESOURCES += \
    fiber2.qrc
TRANSLATIONS += fiber2.ts

