#include "resultview.h"

ResultView::ResultView(HarnessConfigModel *model, QWidget *parent) :
    QLabel(parent),m_model(model)
{
    resize(100,100);
    //setStyleSheet("background-color: red;");
}

void ResultView::setresult(const DefectResultModel *resultmodel)
{

    QList<HarnessConfig> list = m_model->configs();
    //qDebug()<< "list.size():" << list.size();
    for(int i= 0;i< list.size(); i++)
    {
        QModelIndex index = resultmodel->index(i,1);
        bool pass = resultmodel->data(index,Qt::EditRole).toBool();
        int order = i + 1;
         m_model->seterror(order, !pass);
    }
    reload();
}

void ResultView::reload()
{
    emit update();
}

void ResultView::paintEvent(QPaintEvent *)
{
    int width = (m_model->maxradius() + 20)*2;
    int radiusout = m_model->maxradius();
    int radiusin = m_model->inradius()+5;
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


    QList<HarnessConfig> list = m_model->configs();
    //qDebug()<<"listRows:"<<list.count();
    QPixmap pixmapgreen(":/icons/greenStone.png");
    QPixmap pixmapred(":/icons/redStone.png");
    foreach(HarnessConfig config, list)
    {
        if(config.location())
        {
            paint->drawPixmap(config.point().x()-radiusin,config.point().y()-radiusin,2*radiusin,2*radiusin,QPixmap(":/icons/yellowStone.png"));
            //paint->setBrush(QBrush(Qt::gray,Qt::SolidPattern));
            //paint->drawEllipse(config.point(),radiusin,radiusin);
        }
        else if(config.error())
        {
            paint->drawPixmap(config.point().x()-radiusin,config.point().y()-radiusin,2*radiusin,2*radiusin,QPixmap(":/icons/redStone.png"));
            //paint->drawPixmap(config.point(),QPixmap(":/icons/redStone.png"), QRect(config.point().x()-radiusin, config.point().y()-radiusin, 2*radiusin,2*radiusin));
            //paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
            //paint->drawEllipse(config.point(),radiusin,radiusin);
        }
        else
        {
            paint->drawPixmap(config.point().x()-radiusin,config.point().y()-radiusin,2*radiusin,2*radiusin,QPixmap(":/icons/greenStone.png"));
            //paint->drawPixmap(config.point(),QPixmap(":/icons/greenStone.png"), QRect(config.point().x()-radiusin, config.point().y()-radiusin, 2*radiusin,2*radiusin));
            //paint->setBrush(QBrush(Qt::green,Qt::SolidPattern));
            //paint->drawEllipse(config.point(),radiusin,radiusin);
        }

    }
    //paint->drawPixmap(0,0,100,100,QPixmap(":/icons/redStone.png"));
    paint->end();
    delete paint;
}
