#ifndef DEFECTRESULTMODEL_H
#define DEFECTRESULTMODEL_H
#include <QStandardItemModel>
class DefectResultItem
{
public:
    explicit DefectResultItem(int index, const QVector<QVariant> &data);

    QVariant data(int column) const;
    bool setData(int column, const QVariant &value);
    int index() const;
private:
    QVector<QVariant> itemData;
    int m_index;

};
class DefectResultModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DefectResultModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    bool loadresult(const bool isGongtou);
    void clear();

    int status() const;

private:
    QList<DefectResultItem*> m_configs;
    QVector<QVariant> headtitles;
    bool setupModelData(const QString &xml);
    void refrushModel();
    int m_status;
};

#endif // DEFECTRESULTMODEL_H
