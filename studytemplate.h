#ifndef TESTQMPAGE_H
#define TESTQMPAGE_H
#include <QtWidgets>
#include <QLineEdit>
#include "sysuser.h"
class StudyTemplate : public QDialog
{
    Q_OBJECT
public:
    StudyTemplate(QWidget *parent = 0);
private:
    QLineEdit *oldpwdEdit;
    QLineEdit *newpwdEdit;
    QLineEdit *newpwdconfirmEdit;
    bool modify();
    QLabel *newpwdconfirmLabel;
};
#endif // TESTQMPAGE_H
