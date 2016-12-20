#ifndef RESULTVIEW_H
#define RESULTVIEW_H
#include <QtWidgets>
#include <QPainter>
#include "harnessconfigmodel.h"
#include "defectresultmodel.h"
class ResultView : public QLabel
{
    Q_OBJECT

public:
    explicit ResultView(HarnessConfigModel *model, QWidget *parent = 0);
    void setresult(const DefectResultModel *resultmodel);
    void reload();

private:
    void paintEvent(QPaintEvent*);
    QPainter *paint;
    int m_flag;
    HarnessConfigModel *m_model;
};

#endif // RESULTVIEW_H
