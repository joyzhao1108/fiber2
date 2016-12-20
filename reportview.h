#ifndef REPORTVIEW_H
#define REPORTVIEW_H

#include <QtWidgets>
#include <QAxWidget>
#include <QAxObject>
class ReportView : public QDialog
{
    Q_OBJECT

public:
    explicit ReportView(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *ev);

signals:
    void windowLoaded() const;
private:
    QTextEdit *wordview;
    QAxWidget *m_pAxWidget;    
    void loadfile();
    void exportToFile();
    //void close();
};

#endif // REPORTVIEW_H
