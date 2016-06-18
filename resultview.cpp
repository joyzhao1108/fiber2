#include "resultview.h"

ResultView::ResultView(int flag, HarnessConfigModel *model, QWidget *parent) :
    QLabel(parent),m_flag(flag),m_model(model)
{
    resize(100,100);
    //setStyleSheet("background-color: red;");
}

void ResultView::setresult(const DefectResultModel *resultmodel)
{

    QList<HarnessConfig> list = m_model->configs(m_flag);
    //qDebug()<< "list.size():" << list.size();
    for(int i= 0;i< list.size(); i++)
    {
        QModelIndex index = resultmodel->index(i,1);
        bool pass = resultmodel->data(index,Qt::EditRole).toBool();
        int order = i + 1;
         m_model->seterror(m_flag, order, !pass);
    }
    emit update();
}

void ResultView::paintEvent(QPaintEvent *)
{
    int width = (m_model->maxradius(m_flag) + 20)*2;
    int radiusout = m_model->maxradius(m_flag);
    int radiusin = m_model->inradius(m_flag);
    paint = new QPainter;

    paint->begin(this);
    paint->setWindow(-(width/2),-(width/2),width, width);
    QPoint point(0,0);
    paint->setRenderHint(QPainter::Antialiasing, true);
    QPalette palette;
    paint->setBrush(QBrush(Qt::darkGray,Qt::SolidPattern));
    paint->drawEllipse(point,radiusout+5,radiusout+5);
    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));
    paint->drawEllipse(point,radiusout,radiusout);

    //paint->setBrush(QBrush(palette.brush(QPalette::Background)));

    //qDebug()<<"strart paint harness:";


    QList<HarnessConfig> list = m_model->configs(m_flag);
    //qDebug()<<"listRows:"<<list.count();
    foreach(HarnessConfig config, list)
    {
        if(config.location())
        {
            paint->setBrush(QBrush(Qt::gray,Qt::SolidPattern));
        }
        else if(config.error())
        {
            paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
        }
        else
        {
            //qDebug()<<"order:"<<config.order();
            paint->setBrush(QBrush(Qt::green,Qt::SolidPattern));
        }
        paint->drawEllipse(config.point(),radiusin,radiusin);
    }
    paint->end();
    delete paint;
}
