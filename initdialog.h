#ifndef INITDIALOG_H
#define INITDIALOG_H
#include <QtWidgets>
class InitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitDialog(QWidget *parent = 0);


private:
    QPushButton *adminPushButton;
    QPushButton *userPushButton;
    QPushButton *exitPushButton;
    QLabel *logoLabel;
    QLabel *companyLabel;
    QLabel *productLabel;

    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);
    QPoint dragPosition;

    void starttest();
    void opensetting();

    void paintEvent(QPaintEvent*);
    QPainter *paint;
};

#endif // INITDIALOG_H
