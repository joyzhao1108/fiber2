#include "DefectResultItem.h"

#include <QStringList>

//! [0]
DefectResultItem::DefectResultItem(const QVector<QVariant> &data, DefectResultItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//! [0]

//! [1]
DefectResultItem::~DefectResultItem()
{
    qDeleteAll(childItems);
}
//! [1]

//! [2]
DefectResultItem *DefectResultItem::child(int number)
{
    return childItems.value(number);
}
//! [2]

//! [3]
int DefectResultItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
int DefectResultItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<DefectResultItem*>(this));

    return 0;
}
//! [4]

//! [5]
int DefectResultItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant DefectResultItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
bool DefectResultItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        DefectResultItem *item = new DefectResultItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool DefectResultItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (DefectResultItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
DefectResultItem *DefectResultItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
bool DefectResultItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

bool DefectResultItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (DefectResultItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool DefectResultItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
//! [11]
