#include "adminsettingdialog.h"
#include "adminsettingpage.h"
AdminSettingDialog::AdminSettingDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Admin Settings Dialog"));
    setWindowIcon(QIcon(":/icons/logo.ico"));
    setFixedSize(800,600);

//    QHBoxLayout *mainLayout = new QHBoxLayout(this);
//    mainLayout->setMargin(5);
//    mainLayout->setSpacing(5);
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);
    contentsWidget->setFixedHeight(500);
    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new ConfigurationPage);
    pagesWidget->addWidget(new AdminPwdChangePage);
    pagesWidget->addWidget(new UserManagePage);
    pagesWidget->addWidget(new TplListPage);

    //pagesWidget->addWidget(new TestQmPage);

    QPushButton *closeButton = new QPushButton(tr("Close"));

    createIcons();
    contentsWidget->setCurrentRow(0);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

}

void AdminSettingDialog::createIcons()
{
    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/query.png"));
    queryButton->setText(tr("System Configuration"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(tr("Admin Password"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/images/update.png"));
    updateButton->setText(tr("User List"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *tplButton = new QListWidgetItem(contentsWidget);
    tplButton->setIcon(QIcon(":/images/query.png"));
    tplButton->setText(tr("Test Template"));
    tplButton->setTextAlignment(Qt::AlignHCenter);
    tplButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);



    connect(contentsWidget, &QListWidget::currentItemChanged, this, &AdminSettingDialog::changePage);
}

void AdminSettingDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
