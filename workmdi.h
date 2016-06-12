#ifndef WORKMDI_H
#define WORKMDI_H
#include <resultview.h>
#include <QtWidgets>
#include "harnessconfigmodel.h"
class WorkMdi : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit WorkMdi(QWidget *parent = 0);

private:
    QString imgFileNameA;
    QString imgFileNameB;
    QString imgFileNameC;


    QFrame * leftFrame;
    QFrame * centerFrame;
    QFrame * rightFrame;
    QPushButton *captureAPushButton;//公头拍摄按钮
    QPushButton *captureBPushButton;//母头拍摄按钮
    QPushButton *captureCPushButton;//光强拍摄按钮(公头)
    QPushButton *startPushButton;//启动分析按钮
    QPushButton *reportPushButton;//导出报告按钮

    QLabel *titleLabel;//标题栏

    QLabel *standardimageLabel;
    QLabel *testimageLabel;

    QLabel *iconStatusLabel;

//    QTabWidget *aTabWidget;
//    QTabWidget *bTabWidget;
//    QTabWidget *cTabWidget;

    ResultView *stausResultView;

//    QTextEdit *xmlATextEdit;
//    QTextEdit *xmlBTextEdit;
//    QTextEdit *xmlCTextEdit;

    QTableView *resultTableView;

    QComboBox *hanessComboBox;//线束类型

    void captureA();
    void captureB();
    void captureC();

    void startanalyze();
    void generatereport();
    void loadresult();

    void changeharness();

    QPainter *painter;
    HarnessConfigModel *configmodel;

};

#endif // WORKMDI_H
