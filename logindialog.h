#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QtWidgets>



class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(bool admin = false, QWidget *parent = 0);


private:
    bool m_isadminlogin;
    QLineEdit *nameLineEdit;
    QLineEdit *pwdLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);
    QPoint dragPosition;

    void paintEvent(QPaintEvent*);
    QPainter *paint;

    void login();

};

#endif // LOGINDIALOG_H
