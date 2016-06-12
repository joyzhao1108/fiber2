#ifndef DEFECTRESULTITEM_H
#define DEFECTRESULTITEM_H
#include <QList>
#include <QVariant>
#include <QVector>

//! [0]
class DefectResultItem
{
public:
    explicit DefectResultItem(const QVector<QVariant> &data, DefectResultItem *parent = 0);
    ~DefectResultItem();

    DefectResultItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    DefectResultItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

private:
    QList<DefectResultItem*> childItems;
    QVector<QVariant> itemData;
    DefectResultItem *parentItem;
};
#endif // DEFECTRESULTITEM_H
