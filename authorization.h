#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QtWidgets>
#include <QPushButton>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
class Authorization:public QDialog
{
     Q_OBJECT
public:
    Authorization(QWidget *parent = nullptr);
    QString getPass();
    QString getLogin();
    bool getConnectInfo();
    ~Authorization();

private:
    QSqlDatabase dbConnect(QString log, QString pass);
    QLineEdit* pass;
    QLineEdit* log;
    bool isConnect = false;
public slots:
     void authButtonClicked();
};

#endif // AUTHORIZATION_H
