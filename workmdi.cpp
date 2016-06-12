#include "workmdi.h"
#include <QtWidgets>
#include "yxenvironment.h"
#include "defectresultmodel.h"
WorkMdi::WorkMdi(QWidget *parent) :
    QMdiSubWindow(parent)
{
    setWindowTitle(tr("MainWindow"));
    QWidget *centralWidget = new QWidget(this);
    setWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    //QBrush b=QBrush(QColor(30,30,30),Qt::FDiagPattern);
    leftFrame = new QFrame;
    centerFrame = new QFrame;
    rightFrame = new QFrame;
    leftFrame->setFrameShape(QFrame::StyledPanel);
    leftFrame->setSizePolicy(QSizePolicy::Fixed);
    centerFrame->setFrameShape(QFrame::StyledPanel);

    rightFrame->setFrameShape(QFrame::StyledPanel);
    rightFrame->setSizePolicy(QSizePolicy::Fixed);
    //leftFrame->setStyleSheet("background-color: #E1EDD1;");
    //    leftFrame->setAutoFillBackground(true);
    //    leftFrame->setBackgroundRole(QPalette::Background);
    //    leftFrame->setPalette(QPalette(QColor(Qt::green)));

    //QVBoxLayout *leftviewLayout = new QVBoxLayout(leftFrame);
    QFormLayout *leftviewLayout = new QFormLayout(leftFrame);
    hanessComboBox = new QComboBox;
    hanessComboBox->addItem(tr("default harness"));
    leftviewLayout->addWidget(hanessComboBox);

    QGridLayout *viewLayout = new QGridLayout(centerFrame);
    viewLayout->setSpacing(2);
    titleALabel = new QLabel(tr("male"));
    titleBLabel = new QLabel(tr("female"));
    titleCLabel = new QLabel(tr("intensity"));
    titleALabel->setAutoFillBackground(true);
    titleALabel->setBackgroundRole(QPalette::Background);
    titleALabel->setPalette(QPalette(QColor(255, 255, 0)));
    viewLayout->addWidget(titleALabel, 0, 0, Qt::AlignCenter);
    viewLayout->addWidget(titleBLabel, 0, 1, Qt::AlignCenter);
    viewLayout->addWidget(titleCLabel, 0, 2, Qt::AlignCenter);

    //mdiArea->setBackground(b);

    imageALabel = new QLabel(tr("pls capture"));
    imageALabel->setScaledContents(true);
    imageALabel->setFixedSize(QSize(200,200));
    imageBLabel = new QLabel(tr("pls capture"));
    imageBLabel->setScaledContents(true);
    imageBLabel->setFixedSize(QSize(200,200));
    imageCLabel = new QLabel(tr("pls capture"));
    imageCLabel->setScaledContents(true);
    imageCLabel->setFixedSize(QSize(200,200));
    viewLayout->addWidget(imageALabel, 1, 0, Qt::AlignCenter);
    viewLayout->addWidget(imageBLabel, 1, 1, Qt::AlignCenter);
    viewLayout->addWidget(imageCLabel, 1, 2, Qt::AlignCenter);

    configmodel = new HarnessConfigModel(this);
    if(configmodel->loadfromfile(YXENVIRONMENT::configDataPath))
    {
        qDebug()<<"loadfromfile success!";
    }

    captureAPushButton = new QPushButton(tr("&capture"));
    connect(captureAPushButton, &QPushButton::clicked, this, &WorkMdi::captureA);
    captureBPushButton = new QPushButton(tr("&capture"));
    connect(captureBPushButton, &QPushButton::clicked, this, &WorkMdi::captureB);
    captureCPushButton = new QPushButton(tr("&capture"));
    connect(captureCPushButton, &QPushButton::clicked, this, &WorkMdi::captureC);
    viewLayout->addWidget(captureAPushButton, 2, 0);
    viewLayout->addWidget(captureBPushButton, 2, 1);
    viewLayout->addWidget(captureCPushButton, 2, 2);
    //iconAStatusLabel = new QLabel;
    //viewLayout->addWidget(iconAStatusLabel, 2, 0);

    aTabWidget = new QTabWidget;
    aTabWidget->setTabPosition(QTabWidget::South);
    imageADoneResultView = new ResultView(0, configmodel);
    xmlATextEdit = new QTextEdit;
    resultATreeView = new QTreeView;
    aTabWidget->addTab(imageADoneResultView, tr("&pic"));
    aTabWidget->addTab(resultATreeView, tr("&list"));
    aTabWidget->addTab(xmlATextEdit, tr("&detail"));

    bTabWidget = new QTabWidget;
    bTabWidget->setTabPosition(QTabWidget::South);
    imageBDoneResultView = new ResultView(1, configmodel);
    xmlBTextEdit = new QTextEdit;
    resultBTreeView = new QTreeView;
    bTabWidget->addTab(imageBDoneResultView, tr("&pic"));
    bTabWidget->addTab(resultBTreeView, tr("&list"));
    bTabWidget->addTab(xmlBTextEdit, tr("&detail"));

    cTabWidget = new QTabWidget;
    cTabWidget->setTabPosition(QTabWidget::South);
    imageCDoneResultView = new ResultView(0, configmodel);
    xmlCTextEdit = new QTextEdit;
    resultCTreeView = new QTreeView;
    cTabWidget->addTab(imageCDoneResultView, tr("&pic"));
    cTabWidget->addTab(resultCTreeView, tr("&list"));
    cTabWidget->addTab(xmlCTextEdit, tr("&detail"));

    viewLayout->addWidget(aTabWidget, 3, 0);
    viewLayout->addWidget(bTabWidget, 3, 1);
    viewLayout->addWidget(cTabWidget, 3, 2);
    viewLayout->setRowStretch(0,1);
    viewLayout->setRowStretch(1,4);
    viewLayout->setRowStretch(2,1);
    viewLayout->setRowStretch(3,5);
    QFormLayout *controlLayout = new QFormLayout(rightFrame);

    startPushButton = new QPushButton(tr("&start"));
    connect(startPushButton, &QPushButton::clicked, this, &WorkMdi::startanalyze);
    reportPushButton = new QPushButton(tr("&report"));
    connect(reportPushButton, &QPushButton::clicked, this, &WorkMdi::generatereport);

    controlLayout->addWidget(startPushButton);
    controlLayout->addWidget(reportPushButton);
    controlLayout->setSpacing(10);

    mainLayout->addWidget(leftFrame);
    //mainLayout->addStretch(20);
    mainLayout->addWidget(rightFrame);
    mainLayout->setStretch(0,6);
    mainLayout->setStretch(1,1);
    imgFileNameA = QString("");
    imgFileNameB = QString("");
    imgFileNameC = QString("");
}

void WorkMdi::captureA()
{
    //QImage image;
    //image.load(":/images/male-test.png");
    QPixmap *p = new QPixmap(":/images/male-test.png");
    imageALabel->setPixmap(p->scaled(imageALabel->size(), Qt::KeepAspectRatio));
    QString tempImagePath = QDir::currentPath() + "/male.png";
    if(p->save(tempImagePath, "BMP", 1))
    {
        imgFileNameA = tempImagePath;
    }
    //imageBLabel->setPixmap(QPixmap::fromImage( imageFemale.scaled(imageBLabel->size(), Qt::KeepAspectRatio)));
}

void WorkMdi::captureB()
{
    QPixmap *p = new QPixmap(":/images/female-test.bmp");
    imageBLabel->setPixmap(p->scaled(imageBLabel->size(), Qt::KeepAspectRatio));
    QString tempImagePath = QDir::currentPath() + "/female.bmp";
    if(p->save(tempImagePath, "BMP", 1))
    {
        imgFileNameB = tempImagePath;
    }
}

void WorkMdi::captureC()
{
    QPixmap *p = new QPixmap(":/images/male-test.png");
    imageCLabel->setPixmap(p->scaled(imageCLabel->size(), Qt::KeepAspectRatio));
    QString tempImagePath = QDir::currentPath() + "/male.png";
    if(p->save(tempImagePath, "BMP", 1))
    {
        imgFileNameC = tempImagePath;
    }
}

void WorkMdi::startanalyze()
{
    char *charConfigName;
    char *charImageA;
    char *charImageB;
    char *charImageC;
    QByteArray ba0 = YXENVIRONMENT::configDataPath.toLocal8Bit();
    charConfigName = ba0.data();
    QByteArray ba1 = imgFileNameA.toLocal8Bit();
    charImageA = ba1.data();
    QByteArray ba2 = imgFileNameB.toLocal8Bit();
    charImageB = ba2.data();
    QByteArray ba3 = imgFileNameC.toLocal8Bit();
    charImageC = ba3.data();
    try
    {
        qDebug()<<"charImageA:"<<charImageA;
        qDebug()<<"charImageB:"<<charImageB;
        qDebug()<<"charImageC:"<<charImageC;
        qDebug()<<"charConfigName:"<<charConfigName;
        YXENVIRONMENT::detectFun(charImageA, charImageC, charConfigName, charImageB);
        loadresult();
    }
    catch(...)
    {
        qDebug()<<"exception";
    }

    QMessageBox::about(this, tr("Analyze"),tr("finished"));
}

void WorkMdi::generatereport()
{
    QMessageBox::about(NULL, "About", "Still <font color='red'>in progress</font>");
}

void WorkMdi::loadresult()
{
    if(!YXENVIRONMENT::detectpath_gong.isNull()) {
        QFile file(YXENVIRONMENT::detectpath_gong);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            xmlATextEdit->setText(tr("Cannot open result file:\n%1").arg(YXENVIRONMENT::detectpath_gong));
        }
        else
        {
            QTextStream in(&file);
            QString xml = in.readAll();
            xmlATextEdit->setText(xml);


            QStringList headers;
            headers << tr("Title") << tr("Description");

            DefectResultModel *model = new DefectResultModel(headers, xml);
            file.close();

            resultATreeView->setModel(model);
            resultATreeView->expandAll();
            for (int column = 0; column < model->columnCount(); ++column)
                resultATreeView->resizeColumnToContents(column);
            imageADoneResultView->setresult(model);
            file.close();
        }

    } else {
        xmlATextEdit->setText(tr("No result file generated."));
    }

    if(!YXENVIRONMENT::detectpath_mu.isNull()) {
        QFile file(YXENVIRONMENT::detectpath_mu);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            xmlBTextEdit->setText(tr("Cannot open result file:\n%1").arg(YXENVIRONMENT::detectpath_mu));
        }
        else
        {
            QTextStream in(&file);
            QString xml = in.readAll();
            xmlBTextEdit->setText(xml);

            file.close();
        }

    } else {
        xmlBTextEdit->setText(tr("No result file generated."));
    }
    if(!YXENVIRONMENT::lightpath.isNull()) {
        QFile file(YXENVIRONMENT::lightpath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            xmlCTextEdit->setText(tr("Cannot open result file:\n%1").arg(YXENVIRONMENT::lightpath));
        }
        else
        {
            QTextStream in(&file);
            QString xml = in.readAll();
            xmlCTextEdit->setText(xml);
            file.close();
        }
    } else {
        xmlCTextEdit->setText(tr("No result file generated."));
    }
}

void WorkMdi::changeharness()
{
    int index = hanessComboBox->currentIndex();
    Q_UNUSED(index);

}
