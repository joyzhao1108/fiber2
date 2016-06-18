#include "templatemodel.h"
#include <QtWidgets>
TemplateModel::TemplateModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    setupModelData();
}

int TemplateModel::rowCount(const QModelIndex &) const
{
    return m_configs.size();
}

int TemplateModel::columnCount(const QModelIndex &) const
{
    return headtitles.size();
}

QVariant TemplateModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole  || role == Qt::EditRole) {
        TemplateConfig *item = m_configs.at(index.row());
        return item->data(index.column());
    }
    return QVariant();
}

QVariant TemplateModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    //        return headtitles.value(section);

    //    return QVariant();

    //    if (role != Qt::DisplayRole)
    //        return QVariant();

    //    if (orientation == Qt::Horizontal)
    //        return headtitles.value(section);
    //    else
    //        return QString("%1").arg(section + 1);

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return headtitles.value(section);
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

bool TemplateModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && index.row() != index.column()
            && role == Qt::EditRole) {
        TemplateConfig *item = m_configs[index.row()];
        item->setData(index.column(), value);


        //between topLeft and bottomRight inclusive)
        emit dataChanged(index, index);

        return true;
    }
    return false;
}

Qt::ItemFlags TemplateModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


void TemplateModel::setupModelData()
{
    headtitles << tr("ID")
               << tr("Title")
               << tr("Model")
               << tr("TotalHoleCount")
               << tr("LocationHoleCount")
               << tr("Creator")
               << tr("Create Date");
    QSettings *settings = new QSettings("fiber.ini", QSettings::IniFormat);
    int size = settings->beginReadArray("Templates");
    QVector<QVariant> columnData;
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        columnData.clear();
        columnData << settings->value("ID").toString()
                   << settings->value("Title").toString()
                   << settings->value("Model").toString()
                   << settings->value("TotalHoleCount").toString()
                   << settings->value("LocationHoleCount").toString()
                   << settings->value("Creator").toString()
                   << settings->value("CreateDate").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
        //beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
        TemplateConfig *configitem = new TemplateConfig(i, columnData);
        m_configs << configitem;
        //endInsertRows();
    }
    settings->endArray();
    delete settings;
}

TemplateConfig::TemplateConfig(int index, const QVector<QVariant> &data)
{
    itemData = data;
    m_index = index;
}

QVariant TemplateConfig::data(int column) const
{
    return itemData.value(column);
}

bool TemplateConfig::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

int TemplateConfig::index() const
{
    return m_index;
}
