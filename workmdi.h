﻿#ifndef WORKMDI_H
#define WORKMDI_H
#include <resultview.h>
#include <QtWidgets>
#include "harnessconfigmodel.h"
#include "templatemodel.h"
class WorkMdi : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit WorkMdi(QWidget *parent = 0);

private:
    QString imgFileNameDefect;
    QString imgFileNameLight;


    QFrame * leftFrame;
    QFrame * centerFrame;
    QFrame * rightFrame;
    QPushButton *autoSelectPushButton;//拍摄按钮


    QPushButton *capturePushButton;//拍摄按钮

    QPushButton *lightTestPushButton;
    QPushButton *defectTestPushButton;
    QPushButton *autoTestPushButton;

    QPushButton *reportPushButton;//导出报告按钮

    QLabel *titleLabel;//标题栏
    QLabel *standardimageLabel;
    QLabel *testimageLabel;
    QLabel *iconStatusLabel;
    QTextEdit *statuslogTextEdit;
    ResultView *statusResultView;
    QTableView *resultTableView;
    QTableView *configTableView;

    QComboBox *hanessComboBox;//线束类型

    void capture();
    void autoselect();
    bool isGongtou;
    void defectanalyzeclicked();
    void lightanalyzeclicked();
    void autoanalyzeclicked();
    void startanalyze(int flag);
    void generatereport();
    void loadresult();
    void changeharness(int index);
    QPainter *painter;
    HarnessConfigModel *configmodel;
    DefectResultModel *resultmodel;
    TemplateModel *templatemodel;
    QStandardItemModel *configparammodel;

    void appendlog(const QString &text);

    void appenderror(const QString &text);

    unsigned int *m_SerialNumber;

};

#endif // WORKMDI_H
