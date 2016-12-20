#ifndef SELFCHECK_H
#define SELFCHECK_H
#include <QtWidgets>

class SelfCheck : public QDialog
{
    Q_OBJECT

public:
    explicit SelfCheck(QWidget *parent = 0);
    int check();
protected:
    void showEvent(QShowEvent *ev);

signals:
    void windowLoaded() const;

private:
    bool isInitialized;
    QTextEdit *selfCheckTextEdit;
    QPushButton *exitButton;

    void appendlog(const QString &text);

    void appenderror(const QString &text);
};

#endif // SELFCHECK_H
