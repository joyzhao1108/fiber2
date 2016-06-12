#include "sysuser.h"
#include <QSettings>

SysUser::SysUser(const QString &username, const QString &password):m_username(username)
{
    QSettings *configIniWrite = new QSettings("user.ini", QSettings::IniFormat);
    QString defaultPwd = "";
    m_isadmin = false;
    if(username == QString("admin"))
    {
        defaultPwd = "admin";
        m_isadmin = true;
    }
    QString pwd = configIniWrite->value(username + QString("/password"), defaultPwd).toString();
    m_isauthenticated = pwd == password;
    delete configIniWrite;
}

SysUser::SysUser(const QString &username):m_username(username)
{
    m_isauthenticated = false;
    m_isadmin = false;
}

bool SysUser::isauthenticated()
{
    return m_isauthenticated;
}

bool SysUser::isadmin()
{
    return m_isadmin;
}


QString SysUser::username() const
{
    return m_username;
}

SysUserModel::SysUserModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int SysUserModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_users.count();
}

QVariant SysUserModel::data(const QModelIndex & index, int role) const {
    //    if (index.row() < 0 || index.row() >= m_configs.count())
    //        return QVariant();
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    const SysUser &config = m_users[index.row()];
    return config.username();
}

void SysUserModel::addSysUser(const SysUser &user)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_users << user;
    endInsertRows();
}

void SysUserModel::loadall()
{
    m_users.clear();
    QSettings *configIniWrite = new QSettings("user.ini", QSettings::IniFormat);
    QStringList users = configIniWrite->childGroups();
    foreach (QString username, users) {
        if(username != "admin")
        {
            addSysUser(SysUser(username));
        }
    }
    delete configIniWrite;
}
