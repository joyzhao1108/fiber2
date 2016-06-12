#include "harnessconfigmodel.h"
#include <QtWidgets>
HarnessConfigModel::HarnessConfigModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void HarnessConfigModel::addHarnessConfig(const HarnessConfig &config)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_configs << config;
    endInsertRows();
}

bool HarnessConfigModel::loadfromfile(const QString &filename)
{
    //Q_UNUSED(filename);
    qDebug()<<"loadfromfile:"<<filename;
    //QList<HarnessConfig> xxconfigs;;
    if(!filename.isNull() && !filename.isEmpty()) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<< tr("Cannot open result file:\n%1").arg(filename);
        }
        else
        {
            QTextStream in(&file);
            int row = 0;
            while (!in.atEnd()) {
                row++;
                QString line = in.readLine();
                QStringList strlist = line.split(" ", QString::SkipEmptyParts);
                QList<int> intlist;

                int nCount = strlist.size();
                for (int i=0; i<nCount; ++i)
                {
                    intlist << static_cast<QString>(strlist.at(i)).toInt();
                }
                //qDebug()<<"intlist:"<<intlist;
                if(nCount>9)
                {
                    nCount = 9;
                }
                if(row == 1)
                {
                    for (int i=0; i<nCount; ++i)
                    {
                        gongtouconfig[i] = intlist.at(i);
                    }
                }
                else if(row == 2)
                {
                    for (int i=0; i<nCount; ++i)
                    {
                        mutouconfig[i] = intlist.at(i);
                    }
                }
                else
                {


                    if(row <= gongtouconfig[8] + 2)
                    {
                        m_gongtouradius = std::max(abs(intlist.at(0)),abs(intlist.at(1)));
                    }
                    else
                    {
                        m_mutouradius = std::max(abs(intlist.at(0)),abs(intlist.at(1)));
                    }
                    bool islocation = false;
                    if(row>(gongtouconfig[8] + 2 - gongtouconfig[7]) && row<=(gongtouconfig[8] + 2))
                    {
                        islocation = true;
                    }
                    if(row>(mutouconfig[8] + gongtouconfig[8] + 2 - mutouconfig[7]) && row<=(mutouconfig[8] + gongtouconfig[8] + 2))
                    {
                        islocation = true;
                    }
                    //qDebug()<<"row:"<<row<<",islocation"<<islocation<<",gongtouconfig[8]:"<<gongtouconfig[8]<<",mutouconfig[8]:"<<mutouconfig[8];
                    addHarnessConfig(HarnessConfig(intlist.at(0),intlist.at(1),intlist.at(2), islocation));

                }
            }
            file.close();
            qDebug()<<"m_gongtouradius:"<<m_gongtouradius;
            qDebug()<<"m_mutouradius:"<<m_mutouradius;
            return true;
        }

    }

    return false;

}
int HarnessConfigModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_configs.count();
}

QVariant HarnessConfigModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_configs.count())
        return QVariant();

    const HarnessConfig &config = m_configs[index.row()];
    if (role == SymbolRole)
        return config.symbol();
    else if (role == PointRole)
        return config.point();
    return QVariant();
}

QList<HarnessConfig> HarnessConfigModel::configs(int flag) const
{
    QList<HarnessConfig> sublist;
    int num;
    int startindex;
    int nCount;
    if(flag==0)
    {
        startindex = 0;
        num = gongtouconfig[8];//-gongtouconfig[7];
    }
    else
    {
        startindex = gongtouconfig[8];
        num = mutouconfig[8];//-mutouconfig[7];
    }
    nCount = startindex + num;
    int size = m_configs.size();
    for (int i=startindex; i<nCount && i< size; ++i)
    {
        sublist << m_configs.at(i);
    }
    return sublist;
}

int HarnessConfigModel::maxradius(int flag) const
{
    int radius;
    if(flag==0)
    {
        radius = gongtouconfig[4];
    }
    else
    {
        radius = m_mutouradius + 80;//mutouconfig[4];
    }
    return radius;
}

int HarnessConfigModel::inradius(int flag) const
{
    int radius;
    if(flag==0)
    {
        radius = gongtouconfig[1];
    }
    else
    {
        radius = mutouconfig[1];
    }
    return radius;
}

void HarnessConfigModel::seterror(int flag, int order)
{
    if(flag==0)
    {
        m_configs[order - 1].seterror();
    }
    else
    {
        m_configs[gongtouconfig[8] + order - 1].seterror();
    }
}

QHash<int, QByteArray> HarnessConfigModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SymbolRole] = "symbol";
    roles[PointRole] = "point";
    return roles;
}

HarnessConfig::HarnessConfig(int x, int y, int order, bool location)
    : m_x(x), m_y(y), m_order(order),m_location(location)
{

}

QPoint HarnessConfig::point() const
{
    return QPoint(m_x, m_y);
}

QString HarnessConfig::symbol() const
{
    return QString("A");
}

bool HarnessConfig::location() const
{
    return m_location;
}

bool HarnessConfig::error() const
{
    return m_error;
}

void HarnessConfig::seterror(bool error)
{
    m_error = error;
}
