#include "usermanagedialog.h"

UserManageDialog::UserManageDialog(bool isedit, const QString &username, QWidget *parent) :
    QDialog(parent),m_isedit(isedit),m_username(username)
{
    setWindowTitle(tr("User Manage Dialog"));
    setWindowIcon(QIcon(":/icons/logo.ico"));

    QLabel *usrLabel = new QLabel(tr("user name:"));
    QLabel *pwdLabel = new QLabel(tr("password:"));
    usrLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
    //pwdLineEdit->setEchoMode(QLineEdit::Password);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(usrLabel,0,0,1,1);
    gridLayout->addWidget(pwdLabel,1,0,1,1);
    gridLayout->addWidget(usrLineEdit,0,1,1,3);
    gridLayout->addWidget(pwdLineEdit,1,1,1,3);
    QPushButton *okBtn = new QPushButton(tr("Save"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(60);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    QVBoxLayout *dlgLayout = new QVBoxLayout;
    dlgLayout->setMargin(40);
    dlgLayout->addLayout(gridLayout);
    dlgLayout->addStretch(40);
    dlgLayout->addLayout(btnLayout);
    setLayout(dlgLayout);
    connect(okBtn,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));

    if(isedit && username.length()>0)
    {
        QSettings *configIniWrite = new QSettings("user.ini", QSettings::IniFormat);
        QString pwd = configIniWrite->value(username + QString("/password"), "123456").toString();
        delete configIniWrite;
        usrLineEdit->setText(username);
        pwdLineEdit->setText(pwd);
    }

}

void UserManageDialog::accept()
{
    QString username = usrLineEdit->text().trimmed();
    QString pwd = pwdLineEdit->text().trimmed();
    if(pwd.length() < 4 || username.length() < 3)
    {
        QMessageBox::warning(this,tr("Warning"),tr("length is not valid!"),QMessageBox::Yes);
    }
    else
    {
        QSettings *configIniWrite = new QSettings("user.ini", QSettings::IniFormat);
        if(m_isedit)
        {
            configIniWrite->remove(m_username);
            configIniWrite->setValue(username + QString("/password"),pwd);
        }
        else
        {
            if(!configIniWrite->contains(username))
            {
                configIniWrite->setValue(username + QString("/password"),pwd);
            }
            else
            {
                QMessageBox::warning(this,tr("Warning"),tr("user name exists"),QMessageBox::Yes);
                usrLineEdit->setFocus();
            }
        }


        delete configIniWrite;
        QMessageBox::information(this,tr("Success"),tr("operate success!"),QMessageBox::Yes);
        QDialog::accept();
    }
}
