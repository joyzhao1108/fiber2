#ifndef DEFECTRESULTMODEL_H
#define DEFECTRESULTMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QDomDocument>
class DefectResultItem;

//! [0]
class DefectResultModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    DefectResultModel(const QStringList &headers, const QString &data,
              QObject *parent = 0);
    ~DefectResultModel();


    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
//! [1]

//! [2]
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

private:
    void setupModelData(const QDomDocument &doc, DefectResultItem *parent);
    DefectResultItem *getItem(const QModelIndex &index) const;

    DefectResultItem *rootItem;
};

#endif // DEFECTRESULTMODEL_H
