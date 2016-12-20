#include "reportview.h"

ReportView::ReportView(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("ReportView"));
    setWindowIcon(QIcon(":/icons/logo.ico"));

    resize(800,600);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    setLayout(mainLayout);
    //QAxWidget *word=new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);

    wordview = new QTextEdit;
    wordview->setReadOnly(true);
    QFrame *leftFrame = new QFrame;
    QFrame *rightFrame = new QFrame;
    leftFrame->setFrameShape(QFrame::StyledPanel);
    rightFrame->setFrameShape(QFrame::StyledPanel);

    QVBoxLayout *leftviewLayout = new QVBoxLayout(leftFrame);
    leftviewLayout->addWidget(wordview);

    QVBoxLayout *controlLayout = new QVBoxLayout(rightFrame);

    QPushButton *exportPushButton = new QPushButton(QIcon(":/icons/bottom.png"), tr("&export"), this);
    connect(exportPushButton, &QPushButton::clicked, this, &ReportView::exportToFile);
    QPushButton *exitPushButton = new QPushButton(QIcon(":/icons/exit.png"), tr("&Quit"), this);
    connect(exitPushButton, &QPushButton::clicked, this, &QDialog::hide);

    controlLayout->addWidget(exportPushButton);
    controlLayout->addSpacing(20);
    QFrame *line = new QFrame(this);
    line->setGeometry(QRect(40, 180, 400, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->raise();
    controlLayout->addWidget(line);
    controlLayout->addSpacing(20);
    controlLayout->addWidget(exitPushButton);
    controlLayout->addStretch();
    controlLayout->setSpacing(10);

    mainLayout->addWidget(leftFrame);
    mainLayout->addWidget(rightFrame);
    mainLayout->setStretch(0,4);
    mainLayout->setStretch(1,1);

    connect(this, &ReportView::windowLoaded, this, &ReportView::loadfile, Qt::ConnectionType(Qt::QueuedConnection | Qt::UniqueConnection));

    emit windowLoaded();

    //QAxObject *document = m_pAxWidget->querySubObject("ActiveDocument");
    //document->dynamicCall("SaveAs (const QString&)", QString("e:/test/docbyqt.doc"));

    //    QAxObject *pStandard = m_pAxWidget->querySubObject( "CommandBars( const QVariant & )", "Standard" );
    //    pStandard->dynamicCall( "Enabled", true );
    //    pStandard->dynamicCall( "Visible", true );
    //    QAxObject *pFormatting = m_pAxWidget->querySubObject( "CommandBars( const QVariant & )", "Formatting" );
    //    pFormatting->dynamicCall( "Enabled", true );
    //    pFormatting->dynamicCall( "Visible", true );

    //    qDebug() << pStandard->generateDocumentation();
    //    qDebug() << pFormatting->generateDocumentation();

    //    //Start Word
    //    my_app = new QAxObject("Word.Application", this);
    //    QAxObject* my_docs = my_app->querySubObject("Documents");

    //    //Open newDocName
    //    QVariant filename(newDocName);
    //    QVariant confirmconversions(false);
    //    QVariant readonly(false);
    //    QVariant addtorecentfiles(false);
    //    QVariant passworddocument("");
    //    QVariant passwordtemplate("");
    //    QVariant revert(false);
    //    QAxObject* doc = my_docs->querySubObject("Open(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)", filename,confirmconversions, readonly, addtorecentfiles, passworddocument, passwordtemplate,	revert);

    //    //Pull out active document object
    //    QAxObject* active_doc = my_app->querySubObject("ActiveDocument");

    //    QVariant newFileName(fileNameString);
    //    QVariant fileFormat(10); //Saving as filtered html
    //    QVariant LockComments(false);
    //    QVariant Password("");
    //    QVariant recent(true);
    //    QVariant writePassword("");
    //    QVariant ReadOnlyRecommended(false);

    //    active_doc->querySubObject("SaveAs(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)",    newFileName, fileFormat, LockComments, Password, recent, writePassword, ReadOnlyRecommended);
}

void ReportView::showEvent(QShowEvent *ev)
{
    QDialog::showEvent(ev);

}


void ReportView::loadfile()
{
    qDebug() << "C:/report2003.dot";
    QString qsFileName( "C:/report2003.dot" );
    //delete m_pAxWidget;
    m_pAxWidget = new QAxWidget("Word.Document", wordview, Qt::MSWindowsOwnDC);
    m_pAxWidget->setGeometry (wordview->rect());
    m_pAxWidget->setProperty("Visible", true);
    m_pAxWidget->setControl(qsFileName);
    m_pAxWidget->show();
}

void ReportView::exportToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Report"),
                                                    "./report",
                                                    tr("*.doc"));

    if (!fileName.isNull())
    {
        fileName.append(".doc");
        qDebug() << fileName;
        m_pAxWidget->dynamicCall("SaveAs (const QString&)", fileName);

//        if(! ( img2->save(filename) ) ) //保存图像
//        {
//            QMessageBox::information(this,
//                                     tr("Failed to save the image"),
//                                     tr("Failed to save the image!"));
//            return;
//        }
    }
    else
    {
        //cancel
    }
}

