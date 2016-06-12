#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createNew();
    void createActions();
    QMdiArea *mdiArea;
    QAction *quitAction;
    QAction *createNewAction;
};

#endif // MAINWINDOW_H
