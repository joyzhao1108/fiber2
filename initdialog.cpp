#include "initdialog.h"
#include "logindialog.h"
#include "mainwindow.h"
#include "adminsettingdialog.h"
InitDialog::InitDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("product name"));
    setWindowIcon(QIcon(":/icons/logo.ico"));
    resize(600,200);
    //setGeometry(100,100,200,200);
    setStyleSheet("background-color: #efefef;");
    //setStyleSheet("QPushButton { background-color: red }");
    QFrame *topFrame = new QFrame(this);
    QGridLayout * gridLayout = new QGridLayout(topFrame);
    logoLabel = new QLabel(tr("logo"));
    QPixmap *p = new QPixmap(":/icons/logo");
    logoLabel->setPixmap(p->scaled(QSize(50,50), Qt::KeepAspectRatio));
    companyLabel = new QLabel(tr("company name"));
    QFont font  = QApplication::font();
    font.setBold(true);
    font.setPointSize(14);
    companyLabel->setFont(font);
    productLabel = new QLabel(tr("product name"));
    gridLayout->addWidget(logoLabel, 0,0,2,1,Qt::AlignCenter);
    gridLayout->addWidget(companyLabel, 0,1,Qt::AlignCenter);
    gridLayout->addWidget(productLabel, 1,1,Qt::AlignCenter);
    gridLayout->setColumnStretch(0,1);
    gridLayout->setColumnStretch(1,4);

    QFrame *bottomFrame = new QFrame(this);
    QHBoxLayout * hxboLayout = new QHBoxLayout(bottomFrame);
    adminPushButton= new QPushButton(tr("Admin Setting"));
    userPushButton= new QPushButton(tr("Start Test"));
    exitPushButton= new QPushButton(tr("Quit"));
    connect(adminPushButton,&QPushButton::clicked, this, &InitDialog::opensetting);
    connect(userPushButton,&QPushButton::clicked, this, &InitDialog::starttest);
    connect(exitPushButton,&QPushButton::clicked, this, &QDialog::reject);
    hxboLayout->addWidget(adminPushButton);
    hxboLayout->addWidget(userPushButton);
    hxboLayout->addWidget(exitPushButton);
    //hxboLayout->setContentsMargins(100, 10, 100, 10);
    hxboLayout->setSpacing(40);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topFrame);
    mainLayout->addWidget(bottomFrame);
    mainLayout->setContentsMargins(60, 5, 60, 5);
    setLayout(mainLayout);

}



void InitDialog::opensetting()
{
    hide();
    LoginDialog dlg(true);
    dlg.setWindowFlags(Qt::WindowTitleHint);
    if(dlg.exec() == QDialog::Accepted)
    {
        qDebug()<<"Login Admin success!";
        done(7);

    }
    else
    {
        show();
    }
}
void InitDialog::starttest()
{
    hide();
    LoginDialog dlg(false);
    dlg.setWindowFlags(Qt::WindowTitleHint);
    if(dlg.exec() == QDialog::Accepted)
    {
        qDebug()<<"Login Tester success!";
        done(8);

    }
    else
    {
        show();
    }

}


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
