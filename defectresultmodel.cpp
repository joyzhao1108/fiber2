#include "yxenvironment.h"
#include "defectresultmodel.h"
#include <QtWidgets>
#include <QDomDocument>
DefectResultModel::DefectResultModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    headtitles << tr("Touch Point")
               << tr("IsPass")
               << tr("Defect Count")
               << tr("Light Rank")+ tr("(db)");
}

int DefectResultModel::rowCount(const QModelIndex &) const
{
    return m_configs.size();
}

int DefectResultModel::columnCount(const QModelIndex &) const
{
    return headtitles.size();
}


QVariant DefectResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter);
    } else if (role == Qt::DisplayRole  || role == Qt::EditRole) {
        DefectResultItem *item = m_configs.at(index.row());
        if(index.column() == 1 && role == Qt::DisplayRole)
        {
            bool pass = item->data(1).toBool();
            if(pass)
            {
                return QVariant(tr("Pass"));
            }
            else
            {
                return QVariant(tr("Not Pass"));
            }
        }
        return item->data(index.column());
    }
    if(index.column() == 0)
    {
        if(role == Qt::DecorationRole)
        {
            DefectResultItem *item = m_configs.at(index.row());
            bool pass = item->data(1).toBool();
            if(pass)
            {
                return QIcon(":/icons/greenStone.png");
            }
            else
            {
                return QIcon(":/icons/redStone.png");
            }
        }
    }
    return QVariant();
}


QVariant DefectResultModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return headtitles.value(section);
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}



bool DefectResultModel::loadresult(const bool isGongtou)
{
    bool callback = false;
    if(!YXENVIRONMENT::detectpath.isNull()) {
        QFile file(YXENVIRONMENT::detectpath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString xml = in.readAll();
            file.close();
            callback = setupModelData(xml);
        }
    }
    return callback;
}

void DefectResultModel::clear()
{
    beginResetModel();
    m_configs.clear();
    endResetModel();
}

int DefectResultModel::status() const
{
    return m_status;
}

bool DefectResultModel::setupModelData(const QString &xml)
{
    bool callback = false;
    m_status = 1;
    QDomDocument doc;
    if(doc.setContent(xml))
    {
        beginResetModel();
        m_configs.clear();

        QDomElement element;
        QDomNode childnode;
        int seqno;
        QString title;
        bool pass;
        int defectcount;
        int lightrank;
        QVector<QVariant> columnData;
        QDomNodeList list = doc.elementsByTagName("Result");
        for(int i=0;i<list.count();i++){
            element=list.at(i).toElement();
            QDomElement lightRankNode = element.firstChildElement("lightRank");
            QDomElement defectcountNode = element.firstChildElement("defectcount");
            QDomElement seqnoNode = element.firstChildElement("order");
            seqno = seqnoNode.text().toInt();
            title = "hup_" + QString::number(seqno + 1);

            QDomNodeList radchilds = element.elementsByTagName("rad");
            defectcount = defectcountNode.text().toInt();
            lightrank = lightRankNode.text().toInt();
            pass = (defectcount < 4);
            if(!pass)
            {
                m_status = -1;
            }
            columnData.clear();
            columnData << title << pass << defectcount << lightrank;

            DefectResultItem *resultitem = new DefectResultItem(seqno, columnData);
            m_configs << resultitem;
            callback = true;
        }
        endResetModel();
    }
    return callback;

}

void DefectResultModel::refrushModel()
{

}
DefectResultItem::DefectResultItem(int index, const QVector<QVariant> &data)
{
    itemData = data;
    m_index = index;
}

QVariant DefectResultItem::data(int column) const
{
    return itemData.value(column);
}

bool DefectResultItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

int DefectResultItem::index() const
{
    return m_index;
}
