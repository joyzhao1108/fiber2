
#include <QtWidgets>
#include <QDomDocument>
#include "defectresultitem.h"
#include "defectresultmodel.h"

//! [0]
DefectResultModel::DefectResultModel(const QStringList &headers, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    rootItem = new DefectResultItem(rootData);
    QDomDocument doc;
    if(!doc.setContent(data))
    {
        qDebug() << "setcontent for do error";
    }
    setupModelData(doc, rootItem);
}
//! [0]

//! [1]
DefectResultModel::~DefectResultModel()
{
    delete rootItem;
}

//! [1]

//! [2]
int DefectResultModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}
//! [2]

QVariant DefectResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    DefectResultItem *item = getItem(index);

    return item->data(index.column());
}

//! [3]
Qt::ItemFlags DefectResultModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
//! [3]

//! [4]
DefectResultItem *DefectResultModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        DefectResultItem *item = static_cast<DefectResultItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant DefectResultModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//! [5]
QModelIndex DefectResultModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    //! [5]

    //! [6]
    DefectResultItem *parentItem = getItem(parent);

    DefectResultItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//! [6]

bool DefectResultModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool DefectResultModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    DefectResultItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex DefectResultModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DefectResultItem *childItem = getItem(index);
    DefectResultItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool DefectResultModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool DefectResultModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    DefectResultItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int DefectResultModel::rowCount(const QModelIndex &parent) const
{
    DefectResultItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool DefectResultModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    DefectResultItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool DefectResultModel::setHeaderData(int section, Qt::Orientation orientation,
                                      const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void DefectResultModel::setupModelData(const QDomDocument &doc, DefectResultItem *parent)
{
    QDomNode node;
    QDomNode childnode;
    int seqno;
    QString title;
    QString description;
    QVector<QVariant> columnData;
    QDomNodeList list = doc.elementsByTagName("detectDefect");
    for(int i=0;i<list.count();i++){
        node=list.at(i);
        //qDebug()<<"node.firstChild().toElement().text():"<<node.firstChild().toElement().text();
        seqno = node.firstChild().toElement().text().toInt();
        //qDebug()<<"seqno:"<<seqno;

        title = "hup_" + QString::number(seqno + 1);
        description = "";
        columnData.clear();
        columnData << title << description;
        parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
        DefectResultItem *thisitem = parent->child(parent->childCount() - 1);
        for (int column = 0; column < columnData.size(); ++column)
            thisitem->setData(column, columnData[column]);

        QDomNodeList childs = node.childNodes();
        for(int j=1;j<childs.count();j++){
            childnode=childs.at(j);
            title = "rad_" + QString::number(j);
            description = childnode.toElement().text();
            columnData.clear();
            columnData << title << description;
            thisitem->insertChildren(thisitem->childCount(), 1, rootItem->columnCount());
            DefectResultItem *raditem = thisitem->child(thisitem->childCount() - 1);
            for (int column = 0; column < columnData.size(); ++column)
                raditem->setData(column, columnData[column]);
        }
    }

}
