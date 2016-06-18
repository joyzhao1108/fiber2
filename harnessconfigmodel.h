#ifndef HARNESSCONFIGDATA_H
#define HARNESSCONFIGDATA_H

#include <QAbstractListModel>
#include <QStringList>

class HarnessConfig
{
public:
    explicit HarnessConfig(int x, int y, int order, bool location);


    QPoint point() const;
    QString symbol() const;
    bool location() const;
    bool error() const;
    void seterror(bool error = true);
    int order() const;

private:
    QString m_symbol;
    int m_order;
    int m_x;
    int m_y;
    bool m_location;
    bool m_error;

};
class HarnessConfigModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum HarnessConfigRoles {
        SymbolRole = Qt::UserRole + 1,
        PointRole
    };
    HarnessConfigModel(QObject *parent = 0);
    void addHarnessConfig(const HarnessConfig &config);


    bool loadfromfile(const QString &filename);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int gongtouconfig[9];
    int mutouconfig[9];
    QList<HarnessConfig> configs(int flag) const;
    int maxradius(int flag) const;
    int inradius(int flag) const;
    void seterror(int flag, int order, bool error = true);
    QString getconfigdatafilepath() const;
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<HarnessConfig> m_configs;
    int m_gongtouradius;
    int m_mutouradius;
    QString m_configFiePath;
};

#endif // HARNESSCONFIGDATA_H
