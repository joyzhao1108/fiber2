#include "adminsettingpage.h"
#include "usermanagedialog.h"
#include "templatemodel.h"
ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Server configuration"));
    QFormLayout *formLayout = new QFormLayout;
    filepathLineEdit = new QLineEdit;

    //    QHBoxLayout *huiduLayout = new QHBoxLayout;
    //    huiduSpinBox1 = new QSpinBox;
    //    huiduSpinBox2 = new QSpinBox;
    //    huiduLayout->addWidget(huiduSpinBox1);
    //    huiduLayout->addWidget(huiduSpinBox2);
    lightrankLineEdit = new QLineEdit;
    lightrankLineEdit->setValidator(new QIntValidator(0, 1000, this));
    //    rankcountLineEdit = new QLineEdit;
    radLineEdit = new QLineEdit;
    QDoubleValidator*validator=new QDoubleValidator(0,99,8,this);

    validator->setNotation(QDoubleValidator::StandardNotation);
    radLineEdit->setValidator(validator);
    //    formLayout->addRow(tr("&File Path:"), filepathLineEdit);
    //    formLayout->addRow(tr("&HuiDu Section:"), huiduLayout);
    QPushButton *startUpdateButton = new QPushButton(tr("Save"));

    formLayout->addRow(tr("&Light Rank:"), lightrankLineEdit);
    formLayout->addRow(tr("&Radius:"), radLineEdit);

    configGroup->setLayout(formLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(startUpdateButton, &QPushButton::clicked, this, &ConfigurationPage::save);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QSettings *settings = new QSettings("fiber.ini", QSettings::IniFormat);
    settings->setIniCodec(codec);
    settings->beginGroup("SysConfigs");
    lightrankLineEdit->setText(settings->value("LightRankLowBound", 200).toString());
    radLineEdit->setText(settings->value("RadiusLimit", 1.5000000).toString());
    settings->endGroup();
    delete settings;
}

bool ConfigurationPage::save()
{
    bool success = false;
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QSettings *settings = new QSettings("fiber.ini", QSettings::IniFormat);
    settings->setIniCodec(codec);
    settings->beginGroup("SysConfigs");
    settings->setValue("RadiusLimit", radLineEdit->text().toDouble());
    settings->setValue("LightRankLowBound", lightrankLineEdit->text().toInt());
    settings->endGroup();
    delete settings;
    success=true;
    if(success)
    {
        QMessageBox::information(this,tr("Success"),tr("updated success!"),QMessageBox::Yes);
    }
    return success;
}

AdminPwdChangePage::AdminPwdChangePage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *updateGroup = new QGroupBox(tr("Admin Password Modify"));

    QLabel *oldpwdLabel = new QLabel(tr("Old Password:"));
    oldpwdEdit = new QLineEdit;
    oldpwdEdit->setEchoMode(QLineEdit::Password);

    QLabel *newpwdLabel = new QLabel(tr("New Password:"));
    newpwdEdit = new QLineEdit;
    newpwdEdit->setEchoMode(QLineEdit::Password);

    QLabel *newpwdconfirmLabel = new QLabel(tr("Password Confirm:"));
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

    connect(startUpdateButton, &QPushButton::clicked, this, &AdminPwdChangePage::modify);
}

bool AdminPwdChangePage::modify()
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

UserManagePage::UserManagePage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *packageGroup = new QGroupBox(tr("User List"));

    usermodel = new SysUserModel(this);
    usermodel->loadall();
    packageList = new QListView;
    packageList->setModel(usermodel);

    qDebug() << "UserManagePage install sucess!";

    QPushButton *addButton = new QPushButton(tr("Add"));
    QPushButton *editButton = new QPushButton(tr("Edit"));
    QPushButton *delButton = new QPushButton(tr("Delete"));
    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(addButton);
    serverLayout->addWidget(editButton);
    serverLayout->addWidget(delButton);

    QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageLayout->addLayout(serverLayout);
    packageGroup->setLayout(packageLayout);



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packageGroup);

    mainLayout->addSpacing(12);
    //mainLayout->addWidget(addButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &UserManagePage::addUser);
    connect(editButton, &QPushButton::clicked, this, &UserManagePage::editUSer);
    connect(delButton, &QPushButton::clicked, this, &UserManagePage::delUser);
}

void UserManagePage::addUser()
{
    UserManageDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        usermodel->loadall();
    }
}

void UserManagePage::delUser()
{
    QString username = usermodel->data(packageList->currentIndex()).toString();
    QSettings *configIniWrite = new QSettings("user.ini", QSettings::IniFormat);
    configIniWrite->remove(username);
    delete configIniWrite;
    usermodel->loadall();
    QMessageBox::information(this,tr("Success"),tr("operate success!"),QMessageBox::Yes);

}

void UserManagePage::editUSer()
{
    QString username = usermodel->data(packageList->currentIndex()).toString();
    if(username.isEmpty())
    {
        return;
    }
    UserManageDialog *dlg = new UserManageDialog(true,username, this);
    if(dlg->exec() == QDialog::Accepted)
    {
        usermodel->loadall();
    }
}


TplListPage::TplListPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *packageGroup = new QGroupBox(tr("Test Template List"));

    TemplateModel *modeltemplate = new TemplateModel;
    QTableView *tableView = new QTableView;
    tableView->setModel(modeltemplate);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton *addButton = new QPushButton(tr("Add"));
    QPushButton *editButton = new QPushButton(tr("Edit"));
    QPushButton *delButton = new QPushButton(tr("Delete"));
    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(addButton);
    serverLayout->addWidget(editButton);
    serverLayout->addWidget(delButton);

    QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(tableView);
    packageLayout->addLayout(serverLayout);
    packageGroup->setLayout(packageLayout);



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packageGroup);

    //mainLayout->addSpacing(12);
    //mainLayout->addWidget(addButton);
    //mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &TplListPage::addnew);
}

void TplListPage::addnew()
{
    //StudyTemplate *page1 = new StudyTemplate(this);
    //page1->show();
}
