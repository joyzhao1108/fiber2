#ifndef RESULTVIEW_H
#define RESULTVIEW_H
#include <QtWidgets>
#include <QPainter>
#include "harnessconfigmodel.h"
#include "defectresultmodel.h"
class ResultView : public QWidget
{
    Q_OBJECT

public:
    explicit ResultView(int flag, HarnessConfigModel *model, QWidget *parent = 0);
    void setresult(const DefectResultModel *resultmodel);

private:
    void paintEvent(QPaintEvent*);
    QPainter *paint;
    int m_flag;
    HarnessConfigModel *m_model;
};

#endif // RESULTVIEW_H
