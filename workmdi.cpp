#include "workmdi.h"
#include <QtWidgets>
#include "yxenvironment.h"
#include "defectresultmodel.h"
#include "Camera_h.h"
WorkMdi::WorkMdi(QWidget *parent) :
    QMdiSubWindow(parent)
{
    setWindowTitle(tr("MainWindow"));
    QWidget *centralWidget = new QWidget(this);
    setWidget(centralWidget);

    configmodel = new HarnessConfigModel(this);
    templatemodel = new TemplateModel(this);

    QVBoxLayout *windowLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    leftFrame = new QFrame;
    centerFrame = new QFrame;
    rightFrame = new QFrame;
    leftFrame->setFrameShape(QFrame::StyledPanel);
    //leftFrame->setSizePolicy(QSizePolicy::Fixed);
    centerFrame->setFrameShape(QFrame::StyledPanel);

    rightFrame->setFrameShape(QFrame::StyledPanel);
    //rightFrame->setSizePolicy(QSizePolicy::Fixed);
    //centerFrame->setStyleSheet("background-color: #ffffff;");
    //    leftFrame->setAutoFillBackground(true);
    //    leftFrame->setBackgroundRole(QPalette::Background);
    //    leftFrame->setPalette(QPalette(QColor(Qt::green)));


    QVBoxLayout *leftviewLayout = new QVBoxLayout(leftFrame);
    hanessComboBox = new QComboBox;
    hanessComboBox->addItem(tr("Please Choose"), -1);
    QSettings *settings = new QSettings("fiber.ini", QSettings::IniFormat);
    int size = settings->beginReadArray("Templates");
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        hanessComboBox->addItem(settings->value("Title").toString(), i);
    }
    settings->endArray();
    delete settings;
    void(QComboBox::*fp)(int)=&QComboBox::currentIndexChanged;
    connect(hanessComboBox, fp, this, &WorkMdi::changeharness);


    statusResultView = new ResultView(configmodel);
    statusResultView->setFixedSize(QSize(200,200));
    statusResultView->hide();

    configparammodel = new QStandardItemModel(14,2);
    configparammodel->setHeaderData(0,Qt::Horizontal,tr("parameter"));
    configparammodel->setHeaderData(1,Qt::Horizontal,tr("value"));

    configparammodel->setItem(0,0,new QStandardItem(tr("Title")));
    configparammodel->setItem(1,0,new QStandardItem(tr("Model")));
    configparammodel->setItem(2,0,new QStandardItem(tr("TotalHoleCount")));
    configparammodel->setItem(3,0,new QStandardItem(tr("LocationHoleCount")));
    configparammodel->setItem(4,0,new QStandardItem(tr("Creator")));
    configparammodel->setItem(5,0,new QStandardItem(tr("CreateDate")));
    configparammodel->setItem(6,0,new QStandardItem(tr("IsGongTou")));
    configparammodel->setItem(7,0,new QStandardItem(tr("DivideHoleRadius")));
    configparammodel->setItem(8,0,new QStandardItem(tr("CirqueOutRadius")));
    configparammodel->setItem(9,0,new QStandardItem(tr("CirqueInRadius")));
    configparammodel->setItem(10,0,new QStandardItem(tr("GongHoughMinRadius")));
    configparammodel->setItem(11,0,new QStandardItem(tr("GongHoughMaxRadius")));
    configparammodel->setItem(12,0,new QStandardItem(tr("MuHoughMinRadius")));
    configparammodel->setItem(13,0,new QStandardItem(tr("MuHoughMaxRadius")));

    configTableView = new QTableView;
    configTableView->setModel(configparammodel);
    configTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    configTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    configTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    autoSelectPushButton = new QPushButton(tr("&autoselect"));
    connect(autoSelectPushButton, &QPushButton::clicked, this, &WorkMdi::autoselect);

    leftviewLayout->addWidget(hanessComboBox);
    leftviewLayout->addWidget(autoSelectPushButton);
    leftviewLayout->addSpacing(20);
    QFrame *line1 = new QFrame(this);
    line1->setGeometry(QRect(40, 180, 400, 3));
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line1->raise();
    leftviewLayout->addWidget(line1);
    leftviewLayout->addSpacing(20);
    leftviewLayout->addWidget(statusResultView, 1, Qt::AlignHCenter);
    leftviewLayout->addWidget(configTableView);
    //leftviewLayout->addStretch();


    QVBoxLayout *centerLayout = new QVBoxLayout(centerFrame);
    centerLayout->setMargin(0);
    QGridLayout *viewLayout = new QGridLayout;
    //viewLayout->setSpacing(2);

    standardimageLabel = new QLabel(tr("pls capture"));
    standardimageLabel->setScaledContents(true);
    standardimageLabel->setAlignment(Qt::AlignCenter);
    standardimageLabel->setFixedSize(QSize(200,200));
    testimageLabel = new QLabel(tr("pls capture"));
    testimageLabel->setScaledContents(true);
    testimageLabel->setAlignment(Qt::AlignCenter);
    testimageLabel->setFixedSize(QSize(200,200));
    statusResultView->hide();
    testimageLabel->hide();
    standardimageLabel->hide();

    statuslogTextEdit = new QTextEdit(tr("Starting test..."));


    resultmodel = new DefectResultModel;
    resultTableView = new QTableView;
    resultTableView->setModel(resultmodel);
    resultTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    resultTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    viewLayout->addWidget(new QLabel(tr("template")), 0, 0, Qt::AlignCenter);
    viewLayout->addWidget(new QLabel(tr("test")), 0, 1, Qt::AlignCenter);
    viewLayout->addWidget(standardimageLabel, 1, 0);
    viewLayout->addWidget(testimageLabel, 1, 1);

    viewLayout->setRowStretch(0,1);
    viewLayout->setRowStretch(1,4);

    titleLabel = new QLabel(tr("Waiting..."));
    titleLabel->setObjectName("titleLabel");
    titleLabel->setProperty("status", "0");
    titleLabel->setFixedHeight(40);
    titleLabel->setAlignment(Qt::AlignCenter);
    //titleLabel->setStyleSheet("background-color: lightblue;");
    centerLayout->addWidget(titleLabel);
    centerLayout->addLayout(viewLayout);
    centerLayout->addWidget(resultTableView);
    centerLayout->addWidget(statuslogTextEdit);


    QVBoxLayout *controlLayout = new QVBoxLayout(rightFrame);

    capturePushButton = new QPushButton(tr("&capture"));
    connect(capturePushButton, &QPushButton::clicked, this, &WorkMdi::capture);
    lightTestPushButton = new QPushButton(tr("&Light Test"));
    connect(lightTestPushButton, &QPushButton::clicked, this, &WorkMdi::lightanalyzeclicked);
    defectTestPushButton = new QPushButton(tr("&Defect Test"));
    connect(defectTestPushButton, &QPushButton::clicked, this, &WorkMdi::defectanalyzeclicked);
    autoTestPushButton = new QPushButton(tr("&Auto Test"));
    connect(autoTestPushButton, &QPushButton::clicked, this, &WorkMdi::autoanalyzeclicked);
    reportPushButton = new QPushButton(tr("&Report Preview"));
    connect(reportPushButton, &QPushButton::clicked, this, &WorkMdi::generatereport);
    controlLayout->addWidget(capturePushButton);
    controlLayout->addSpacing(20);
    QFrame *line = new QFrame(this);
    line->setGeometry(QRect(40, 180, 400, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->raise();
    controlLayout->addWidget(line);
    controlLayout->addSpacing(20);
    controlLayout->addWidget(lightTestPushButton);
    controlLayout->addWidget(defectTestPushButton);
    controlLayout->addWidget(autoTestPushButton);

    controlLayout->addSpacing(20);
    QFrame *line2 = new QFrame(this);
    line2->setGeometry(QRect(40, 180, 400, 3));
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    line2->raise();
    controlLayout->addWidget(line2);
    controlLayout->addSpacing(20);

    controlLayout->addWidget(reportPushButton);
    controlLayout->addStretch();
    controlLayout->setSpacing(10);

    mainLayout->addWidget(leftFrame);
    mainLayout->addWidget(centerFrame);
    mainLayout->addWidget(rightFrame);
    mainLayout->setStretch(0,1);
    mainLayout->setStretch(1,3);
    mainLayout->setStretch(2,1);

    QLabel *productNameLabel = new QLabel(tr("product name"), this);
    productNameLabel->setScaledContents(true);
    productNameLabel->setAlignment(Qt::AlignCenter);
    productNameLabel->setObjectName("productNameLabel");
    productNameLabel->setFixedHeight(60);
    windowLayout->addWidget(productNameLabel);
    windowLayout->addLayout(mainLayout);
    //    imgFileNameDefect = QString("");
    //    imgFileNameLight = QString("");

    int cflag = CameraInit(m_SerialNumber);
    if(cflag == 0)
    {
        appendlog(tr("camera load and init successfully!"));
    }
    else if(cflag == 1)
    {
        appendlog(tr("warining:camera loadded and not recognized usb 3.0!"));
    }
    else
    {
        appenderror(tr("error:camera not find!"));
    }
}

void WorkMdi::capture()
{
    if(hanessComboBox->currentIndex() == 0)
    {
        QMessageBox::warning(this, tr("Warning"), tr("please choose harness type first."));
        return;
    }
    if(isGongtou)
    {
        QPixmap *p = new QPixmap(":/images/male-test.png");
        testimageLabel->setPixmap(p->scaled(testimageLabel->size(), Qt::KeepAspectRatio));
        QString tempImagePath = QDir::currentPath() + "/tempimage.png";
        if(p->save(tempImagePath))
        {
            imgFileNameDefect = tempImagePath;
            imgFileNameLight = tempImagePath;
        }
    }
    else
    {
        QPixmap *p = new QPixmap(":/images/female-test.bmp");
        testimageLabel->setPixmap(p->scaled(testimageLabel->size(), Qt::KeepAspectRatio));
        QString tempImagePath = QDir::currentPath() + "/tempimage.bmp";
        if(p->save(tempImagePath))
        {
            imgFileNameDefect = tempImagePath;
            imgFileNameLight = tempImagePath;
        }
    }
}

void WorkMdi::autoselect()
{
    hanessComboBox->setCurrentIndex(1);
    //hanessComboBox->view()->selectionModel()->setCurrentIndex(hanessComboBox->model()->index(1,hanessComboBox->modelColumn(),hanessComboBox->rootModelIndex()),QItemSelectionModel::ClearAndSelect);
    changeharness(1);
}

void WorkMdi::defectanalyzeclicked()
{
    startanalyze(1);
}

void WorkMdi::lightanalyzeclicked()
{
    startanalyze(3);
}

void WorkMdi::autoanalyzeclicked()
{
    startanalyze(2);
}

void WorkMdi::startanalyze(int flag)
{
    if(hanessComboBox->currentIndex() == 0)
    {
        QMessageBox::warning(this, tr("Warning"), tr("please choose harness type first."));
        return;
    }
    char *charConfigName;
    char *charImageDefect;
    char *charImageLight;
    if(imgFileNameDefect.isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("please capture first."));
        return;
    }
    QByteArray ba0 = configmodel->getconfigdatafilepath().toLocal8Bit();
    charConfigName = ba0.data();
    QByteArray ba1 = imgFileNameDefect.toLocal8Bit();
    charImageDefect = ba1.data();
    QByteArray ba2 = imgFileNameLight.toLocal8Bit();
    charImageLight = ba2.data();
    qDebug() << "charImageDefect:"<< charImageDefect;
    qDebug() << "charImageLight:" << charImageLight;
    qDebug() << "charConfigName:"<< charConfigName;
    qDebug() << "flag:" << flag;
    try
    {
        if(isGongtou)
        {
            YXENVIRONMENT::detectFunM(charImageDefect, charImageLight, charConfigName, flag);
        }
        else
        {
            YXENVIRONMENT::detectFunF(charImageDefect, charImageLight, charConfigName, flag);
        }
        loadresult();
    }
    catch(...)
    {
        appenderror("exception");
    }

    appendlog(tr("Analyze finished"));
}

void WorkMdi::generatereport()
{
    QMessageBox::about(NULL, "About", "Still <font color='red'>in progress</font>");
}

void WorkMdi::loadresult()
{
    bool isloadsuccess = resultmodel->loadresult(true);
    if(isloadsuccess)
    {
        appendlog(tr("result table load finished."));
        statusResultView->setresult(resultmodel);
        appendlog(tr("status view load finished."));

        int status = resultmodel->status();
        titleLabel->setProperty("status", QString::number(status));
        titleLabel->style()->unpolish(titleLabel);
        titleLabel->style()->polish(titleLabel);
        if(status == 0)
        {
            titleLabel->setText(tr("Waiting..."));
        }
        else if(status == 1)
        {
            titleLabel->setText(tr("Success!"));
        }
        else
        {

            titleLabel->setText(tr("Failed!"));
            appenderror(tr("Test Failed."));
        }
    }
    else {
        appenderror(tr("No result file generated."));
    }
}

void WorkMdi::changeharness(int index)
{
    if(index != 0)
    {
        appendlog(tr("You have choosen the %1").arg(hanessComboBox->currentText()));

        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        QSettings *settings = new QSettings("fiber.ini", QSettings::IniFormat);
        settings->setIniCodec(codec);
        settings->beginWriteArray("Templates");
        settings->setArrayIndex(index - 1);
        QString configPath = settings->value("ConfigDataPath").toString();
        QString picPath = settings->value("BasePicPath").toString();
        qDebug() << "configPath:"<< configPath;
        isGongtou = settings->value("IsGongTou").toBool();
        if(configmodel->loadfromfile(configPath, isGongtou))
        {
            statusResultView->show();
            statusResultView->reload();
            QPixmap p(picPath) ;
            standardimageLabel->setPixmap(p.scaled(standardimageLabel->size(), Qt::KeepAspectRatio));
            standardimageLabel->show();
            testimageLabel->show();
            configparammodel->setItem(0,1,new QStandardItem(settings->value("Title").toString()));
            configparammodel->setItem(1,1,new QStandardItem(settings->value("Model").toString()));
            configparammodel->setItem(2,1,new QStandardItem(settings->value("TotalHoleCount").toString()));
            configparammodel->setItem(3,1,new QStandardItem(settings->value("LocationHoleCount").toString()));
            configparammodel->setItem(4,1,new QStandardItem(settings->value("Creator").toString()));
            configparammodel->setItem(5,1,new QStandardItem(settings->value("CreateDate").toDateTime().toString("yyyy-MM-dd hh:mm:ss")));
            configparammodel->setItem(6,1,new QStandardItem(settings->value("IsGongTou").toBool() ? tr("Male") : tr("Female")));
            configparammodel->setItem(7,1,new QStandardItem(settings->value("DivideHoleRadius").toString()));
            configparammodel->setItem(8,1,new QStandardItem(settings->value("CirqueOutRadius").toString()));
            configparammodel->setItem(9,1,new QStandardItem(settings->value("CirqueInRadius").toString()));
            configparammodel->setItem(10,1,new QStandardItem(settings->value("GongHoughMinRadius").toString()));
            configparammodel->setItem(11,1,new QStandardItem(settings->value("GongHoughMaxRadius").toString()));
            configparammodel->setItem(12,1,new QStandardItem(settings->value("MuHoughMinRadius").toString()));
            configparammodel->setItem(13,1,new QStandardItem(settings->value("MuHoughMaxRadius").toString()));

        }
        settings->endArray();
        delete settings;
    }
    else
    {
        statusResultView->hide();
        testimageLabel->hide();
        standardimageLabel->hide();
        configparammodel->setItem(0,1,new QStandardItem(""));
        configparammodel->setItem(1,1,new QStandardItem(""));
        configparammodel->setItem(2,1,new QStandardItem(""));
        configparammodel->setItem(3,1,new QStandardItem(""));
        configparammodel->setItem(4,1,new QStandardItem(""));
        configparammodel->setItem(5,1,new QStandardItem(""));
        configparammodel->setItem(6,1,new QStandardItem(""));
        configparammodel->setItem(7,1,new QStandardItem(""));
        configparammodel->setItem(8,1,new QStandardItem(""));
        configparammodel->setItem(9,1,new QStandardItem(""));
        configparammodel->setItem(10,1,new QStandardItem(""));
        configparammodel->setItem(11,1,new QStandardItem(""));
        configparammodel->setItem(12,1,new QStandardItem(""));
        configparammodel->setItem(13,1,new QStandardItem(""));
    }
    imgFileNameDefect = "";
    imgFileNameLight = "";
    testimageLabel->clear();
    resultmodel->clear();
    titleLabel->setProperty("status", QString::number(0));
    titleLabel->style()->unpolish(titleLabel);
    titleLabel->style()->polish(titleLabel);
    titleLabel->setText(tr("Waiting..."));
}

void WorkMdi::appendlog(const QString &text)
{
    QStringList log;
    log << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << text;
    statuslogTextEdit->append(log.join(":"));
    //statuslogTextEdit->moveCursor(QTextCursor::Start) ;
    //statuslogTextEdit->ensureCursorVisible();
    statuslogTextEdit->verticalScrollBar()->setValue(statuslogTextEdit->verticalScrollBar()->maximum());
}

void WorkMdi::appenderror(const QString &text)
{
    appendlog(QString("<span style=' color:#ff0000;'>%1</span>").arg(text));
}
