#include <QtWidgets>
#include "studytemplate.h"
#include "usermanagedialog.h"
StudyTemplate::StudyTemplate(QWidget *parent)
    : QDialog(parent)
{
    QGroupBox *updateGroup = new QGroupBox(tr("Admin Password Modify"));

    QLabel *oldpwdLabel = new QLabel(tr("Old Password:"));
    oldpwdEdit = new QLineEdit;
    oldpwdEdit->setEchoMode(QLineEdit::Password);

    QLabel *newpwdLabel = new QLabel(tr("New Password:"));
    newpwdEdit = new QLineEdit;
    newpwdEdit->setEchoMode(QLineEdit::Password);

    newpwdconfirmLabel = new QLabel(tr("Password Confirm:"));
    newpwdconfirmEdit = new QLineEdit;
    newpwdconfirmEdit->setEchoMode(QLineEdit::Password);




    QPushButton *startUpdateButton = new QPushButton(tr("Save"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(oldpwdLabel, 0, 0);
    packagesLayout->addWidget(oldpwdEdit, 0, 1);
    packagesLayout->addWidget(newpwdLabel, 1, 0);
    packagesLayout->addWidget(newpwdEdit, 1, 1);
    packagesLayout->addWidget(newpwdconfirmLabel, 2, 0);
    packagesLayout->addWidget(newpwdconfirmEdit, 2, 1);
    updateGroup->setLayout(packagesLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);

    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(startUpdateButton, &QPushButton::clicked, this, &StudyTemplate::modify);
}

bool StudyTemplate::modify()
{
    bool success = false;
    QString oldpwd = oldpwdEdit->text().trimmed();
    QString newpwd = newpwdEdit->text().trimmed();
    QString newpwdconfirm = newpwdconfirmEdit->text().trimmed();
    if(newpwd != newpwdconfirm)
    {
        QMessageBox::warning(this,tr("Warning"),tr("password confirm is not same!"),QMessageBox::Yes);
    }
    else
    {
        if(newpwdconfirm.length() < 4)
        {
            QMessageBox::warning(this,tr("Warning"),tr("new password length must be more 4!"),QMessageBox::Yes);
        }
        else
        {
            QSettings *configIniWrite = new QSettings("user.ini", QSettings::IniFormat);
            QString pwd = configIniWrite->value(QString("admin/password"), "admin").toString();
            if(oldpwd != pwd)
            {
                QMessageBox::warning(this,tr("Warning"),tr("old password is not correct!"),QMessageBox::Yes);
            }
            else
            {
                configIniWrite->setValue(QString("admin/password"),newpwdconfirm);
                success = true;
            }
            delete configIniWrite;
        }
    }
    if(success)
    {
        QMessageBox::information(this,tr("Success"),tr("updated success!"),QMessageBox::Yes);
    }
    return success;
}
