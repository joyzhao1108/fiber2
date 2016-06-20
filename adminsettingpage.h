#ifndef ADMINSETTINGPAGE_H
#define ADMINSETTINGPAGE_H
#include <QtWidgets>
#include <QLineEdit>
#include "sysuser.h"
class AdminPwdChangePage : public QWidget
{
    Q_OBJECT
public:
    AdminPwdChangePage(QWidget *parent = 0);
private:
    QLineEdit *oldpwdEdit;
    QLineEdit *newpwdEdit;
    QLineEdit *newpwdconfirmEdit;
    bool modify();
};

class UserManagePage : public QWidget
{
    Q_OBJECT
public:
    UserManagePage(QWidget *parent = 0);

private:
    SysUserModel *usermodel;    
    QListView *packageList;
    void addUser();
    void delUser();
    void editUSer();
};
class TplListPage : public QWidget
{
    Q_OBJECT
public:
    TplListPage(QWidget *parent = 0);
private:
    void addnew();
};
class ConfigurationPage : public QWidget
{
    Q_OBJECT
public:
    ConfigurationPage(QWidget *parent = 0);
private:
    QLineEdit *filepathLineEdit;
    QSpinBox *huiduSpinBox1;
    QSpinBox *huiduSpinBox2;
    QLineEdit *lightrankLineEdit;
    QLineEdit *rankcountLineEdit;
    QLineEdit *radLineEdit;
    bool save();
};
#endif // ADMINSETTINGPAGE_H
