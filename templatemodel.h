#ifndef TEMPLATEMODEL_H
#define TEMPLATEMODEL_H
#include <QStandardItemModel>
class TemplateConfig
{
public:
    explicit TemplateConfig(int index, const QVector<QVariant> &data);

    QVariant data(int column) const;
    bool setData(int column, const QVariant &value);
    int index() const;
private:
    QVector<QVariant> itemData;
    int m_index;

};
class TemplateModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TemplateModel(QObject *parent = 0);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<TemplateConfig*> m_configs;
    QVector<QVariant> headtitles;
    void setupModelData();

};
#endif // TEMPLATEMODEL_H
