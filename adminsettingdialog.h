#ifndef ADMINSETTINGDIALOG_H
#define ADMINSETTINGDIALOG_H

#include <QtWidgets>

class AdminSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminSettingDialog(QWidget *parent = 0);

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
};

#endif // ADMINSETTINGDIALOG_H
