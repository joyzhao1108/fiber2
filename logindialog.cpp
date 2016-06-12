#include "logindialog.h"
#include <QtWidgets>
#include "sysuser.h"
LoginDialog::LoginDialog(bool admin, QWidget *parent) :
    QDialog(parent),m_isadminlogin(admin)
{
    setWindowTitle(tr("product name"));
    setStyleSheet("background-color: #efefef;");
    this->setWindowIcon(QIcon(":/icons/logo"));
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 2);
    gridLayout->setColumnStretch(2, 2);
    gridLayout->setColumnStretch(3, 1);

    gridLayout->setMargin(15);
    gridLayout->setColumnMinimumWidth(2, 15);

    QLabel *title = new QLabel;
    QFont font  = QApplication::font();
    font.setBold(true);
    font.setPointSize(14);
    title->setFont(font);
    if(admin)
    {
        title->setText(tr("Admin Login Window"));
    }
    else
    {
        title->setText(tr("Test Login Window"));
    }
    QLabel *lbl1 = new QLabel(QWidget::tr("UserName:"));
    nameLineEdit = new QLineEdit;
    nameLineEdit->setStyleSheet("QLineEdit{font: italic large \"Times New Roman\";color:rgb(55,100,255);border:1px solid rgb(155,200,33);border-radius:5px;selection-color:pink}");
    QLabel *lbl2 = new QLabel(QWidget::tr("Password:"));
    pwdLineEdit = new QLineEdit;
    pwdLineEdit->setStyleSheet("QLineEdit{font: italic large \"Times New Roman\";color:rgb(55,100,255);border:1px solid rgb(155,200,33);border-radius:5px;selection-color:pink}");
    pwdLineEdit->setEchoMode(QLineEdit::Password);
    okButton = new QPushButton(tr("&Login"));
    cancelButton = new QPushButton(tr("&Cancel"));
    gridLayout->addWidget(title, 0, 1, 1, 2, Qt::AlignCenter);
    gridLayout->addWidget(lbl1, 1, 1, Qt::AlignCenter);
    gridLayout->addWidget(nameLineEdit, 1, 2, Qt::AlignCenter);
    gridLayout->addWidget(lbl2, 2, 1, Qt::AlignCenter);
    gridLayout->addWidget(pwdLineEdit, 2, 2, Qt::AlignCenter);
    gridLayout->addWidget(okButton, 3, 1, Qt::AlignCenter);
    gridLayout->addWidget(cancelButton, 3, 2, Qt::AlignCenter);

    connect(okButton,&QPushButton::clicked, this, &LoginDialog::login);
    connect(cancelButton,&QPushButton::clicked, this, &QDialog::reject);
    setLayout(gridLayout);
    resize(400,150);
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() &Qt::LeftButton)
    {
        if (dragPosition != QPoint(-1, -1))
            move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = QPoint(-1, -1);
        event->accept();
    }
}

void LoginDialog::paintEvent(QPaintEvent *)
{
    paint=new QPainter;
    paint->begin(this);
    paint->setPen(QPen(Qt::darkBlue,2,Qt::SolidLine));//设置画笔形式
    //paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
    paint->drawRect(0,0,400,150);
    paint->end();
    delete paint;
}

void LoginDialog::login()
{
    SysUser *user = new SysUser(nameLineEdit->text().trimmed(),pwdLineEdit->text().trimmed());
    if(user->isauthenticated() && (user->isadmin() || !m_isadminlogin))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("username or password is wrong!"),QMessageBox::Yes);
        nameLineEdit->clear();
        pwdLineEdit->clear();
        nameLineEdit->setFocus();
    }
}


