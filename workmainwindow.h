#ifndef WORKMAINWINDOW_H
#define WORKMAINWINDOW_H
#include <resultview.h>
#include <QtWidgets>
#include "harnessconfigmodel.h"
#include "templatemodel.h"
#include "reportview.h"
class WorkMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit WorkMainWindow(QWidget *parent = 0);

private:
    QString imgFileNameDefect;
    QString imgFileNameLight;


    QFrame * leftFrame;
    QFrame * centerFrame;
    QFrame * rightFrame;
    QPushButton *autoSelectPushButton;//auto select button


    QPushButton *capturePushButton;//capture button

    QPushButton *lightTestPushButton;
    QPushButton *defectTestPushButton;
    QPushButton *autoTestPushButton;

    QPushButton *reportPushButton;//export report button
    QPushButton *exitPushButton;

    QLabel *titleLabel;//title bar
    QLabel *standardimageLabel;
    QLabel *testimageLabel;


    QTextEdit *statuslogTextEdit;
    ResultView *statusResultView;
    QTableView *resultTableView;
    QTableView *configTableView;
    QTableWidget *photopreviewTableWidget;
    ReportView *reportview;

    QComboBox *hanessComboBox;//hanesstype

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
#endif // WORKMAINWINDOW_H
