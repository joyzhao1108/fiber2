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

bool HarnessConfigModel::loadfromfile(const QString &filename, bool isGongtou)
{
    //Q_UNUSED(filename);
    qDebug()<<"loadfromfile:"<<filename;
    m_configFiePath = filename;
    m_isGongtou = isGongtou;
    m_gongtouradius = 0;
    if(!filename.isNull() && !filename.isEmpty()) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<< tr("Cannot open result file:\n%1").arg(filename);
        }
        else
        {
            beginResetModel();
            m_configs.clear();
            QTextStream in(&file);
            int row = 0;
            while (!in.atEnd()) {
                row++;
                QString line = in.readLine();
                if(line.isEmpty())
                {
                    break;
                }
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
                else
                {
                    int max = std::max(abs(intlist.at(0)),abs(intlist.at(1)));
                    m_gongtouradius = std::max(max,m_gongtouradius);

                    bool islocation = false;
                    if(row>(gongtouconfig[8] + 1 - gongtouconfig[7]) && row<=(gongtouconfig[8] + 1))
                    {
                        islocation = true;
                    }
                    //qDebug()<<"row:"<<row<<",islocation"<<islocation<<",gongtouconfig[8]:"<<gongtouconfig[8]<<",mutouconfig[8]:"<<mutouconfig[8];
                    addHarnessConfig(HarnessConfig(intlist.at(0),intlist.at(1),intlist.at(2), islocation));

                }
            }
            file.close();
            qDebug()<<"m_gongtouradius:"<<m_gongtouradius;

            endResetModel();
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

QList<HarnessConfig> HarnessConfigModel::configs() const
{
    return m_configs;
}

int HarnessConfigModel::maxradius() const
{
    return m_gongtouradius + 80;
}

int HarnessConfigModel::inradius() const
{
    return gongtouconfig[2]+10;
}

void HarnessConfigModel::seterror(int order, bool error)
{
    beginResetModel();
    m_configs[order - 1].seterror(error);
    endResetModel();
}

QString HarnessConfigModel::getconfigdatafilepath() const
{
    return m_configFiePath;

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

int HarnessConfig::order() const
{
    return m_order;
}
