#include "initdialog.h"
#include "logindialog.h"
#include "mainwindow.h"
#include "adminsettingdialog.h"
InitDialog::InitDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("product name"));
    setWindowIcon(QIcon(":/icons/logo.ico"));
    //resize(600,200);
    //setGeometry(100,100,200,200);
    //setStyleSheet("background-color: #efefef;");
    //setStyleSheet("QPushButton { background-color: red }");
    QFrame *topFrame = new QFrame(this);
    QHBoxLayout * hxboLayout = new QHBoxLayout(topFrame);
    logoLabel = new QLabel(tr("logo"));
    QPixmap *p = new QPixmap(":/icons/logo");
    logoLabel->setPixmap(p->scaled(QSize(25,25), Qt::KeepAspectRatio));
    companyLabel = new QLabel(tr("company name"));
    QFont font  = QApplication::font();
    //font.setBold(true);
    //font.setPointSize(16);
    companyLabel->setFont(font);
    hxboLayout->addWidget(logoLabel);
    hxboLayout->addWidget(companyLabel);
    hxboLayout->addStretch(0);
    //gridLayout->addWidget(productLabel, 1,1,Qt::AlignCenter);
    //gridLayout->setColumnStretch(0,1);
    //gridLayout->setColumnStretch(1,4);

    QFrame *bottomFrame = new QFrame(this);
    QVBoxLayout * vxboLayout = new QVBoxLayout(bottomFrame);

    productLabel = new QLabel(tr("product name"));
    productLabel->setObjectName("productNameLabelStartUp");
    adminPushButton= new QPushButton(tr("Admin Setting"));
    userPushButton= new QPushButton(tr("Start Test"));
    exitPushButton= new QPushButton(tr("Quit"));
    connect(adminPushButton,&QPushButton::clicked, this, &InitDialog::opensetting);
    connect(userPushButton,&QPushButton::clicked, this, &InitDialog::starttest);
    connect(exitPushButton,&QPushButton::clicked, this, &QDialog::reject);
    vxboLayout->addWidget(productLabel,0,Qt::AlignCenter);
    vxboLayout->addSpacing(100);
    vxboLayout->addWidget(adminPushButton);
    vxboLayout->addSpacing(20);
    //adminPushButton->setFixedWidth(250);
    vxboLayout->addWidget(userPushButton);
    vxboLayout->addSpacing(20);
    //userPushButton->setFixedWidth(250);
    vxboLayout->addWidget(exitPushButton);
    //exitPushButton->setFixedWidth(250);
    vxboLayout->setContentsMargins(180, 150, 180, 200);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topFrame);
    mainLayout->addWidget(bottomFrame);
    mainLayout->addStretch(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

}



void InitDialog::opensetting()
{
    hide();
    LoginDialog dlg(true);
    dlg.setWindowFlags(Qt::FramelessWindowHint);
    dlg.setWindowState(Qt::WindowFullScreen);
    if(dlg.exec() == QDialog::Accepted)
    {
        qDebug()<<"Login Admin success!";
        done(7);

    }
    else
    {
        done(99);
    }
}
void InitDialog::starttest()
{
    hide();
    LoginDialog dlg(false);
    dlg.setWindowFlags(Qt::FramelessWindowHint);
    dlg.setWindowState(Qt::WindowFullScreen);
    if(dlg.exec() == QDialog::Accepted)
    {
        qDebug()<<"Login Tester success!";
        done(8);

    }
    else
    {
        done(99);
    }

}

/*
void InitDialog::paintEvent(QPaintEvent *)
{
    paint=new QPainter;
    paint->begin(this);
    paint->setPen(QPen(Qt::darkBlue,2,Qt::SolidLine));//设置画笔形式
    //paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
    paint->drawRect(0,0,600,200);
    paint->end();
    delete paint;
    //    QPainterPath path;
    //    path.setFillRule(Qt::WindingFill);
    //    path.addRect(10, 10, this->width()-20, this->height()-20);

    //    QPainter painter(this);
    //    painter.setRenderHint(QPainter::Antialiasing, true);
    //    painter.fillPath(path, QBrush(Qt::white));

    //    QColor color(0, 0, 0, 50);
    //    for(int i=0; i<10; i++)
    //    {
    //        QPainterPath path;
    //        path.setFillRule(Qt::WindingFill);
    //        path.addRoundRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2, 5);
    //        color.setAlpha(150 - qSqrt(i)*50);
    //        painter.setPen(color);
    //        painter.drawPath(path);
    //    }
}

void InitDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void InitDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() &Qt::LeftButton)
    {
        if (dragPosition != QPoint(-1, -1))
            move(event->globalPos() - dragPosition);
        event->accept();
    }
}
void InitDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = QPoint(-1, -1);
        event->accept();
    }
}
*/
