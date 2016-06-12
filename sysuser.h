#ifndef SYSUSER_H
#define SYSUSER_H
#include <QAbstractListModel>
class SysUser
{
public:
    SysUser(const QString &username,const QString &password);
    SysUser(const QString &username);
    bool isauthenticated();
    bool isadmin();
    QString username() const;
private:
    QString m_username;
    bool m_isauthenticated;
    bool m_isadmin;
};

class SysUserModel : public QAbstractListModel
{
    Q_OBJECT

public:
    SysUserModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addSysUser(const SysUser &user);
    void loadall();

private:
    QList<SysUser> m_users;
};

#endif // SYSUSER_H
