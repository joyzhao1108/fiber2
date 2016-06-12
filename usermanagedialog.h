#ifndef USERMANAGEDIALOG_H
#define USERMANAGEDIALOG_H

#include <QtWidgets>


class UserManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManageDialog(bool isedit = false, const QString &username = "", QWidget *parent = 0);
    void accept() override;
private:
    QLineEdit *usrLineEdit;
    QLineEdit *pwdLineEdit;
    bool m_isedit;
    QString m_username;
};

#endif // USERMANAGEDIALOG_H
