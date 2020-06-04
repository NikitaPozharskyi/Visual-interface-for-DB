#ifndef DATASELECT_H
#define DATASELECT_H

#include <QDialog>
#include <QtWidgets>
#include <QPushButton>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "authorization.h"
class DialogMain:public QDialog
{
     Q_OBJECT
public:
    DialogMain(QWidget *parent = nullptr);
    QString getDataName();
    QPushButton* dbButt;
    QString getPass();
    QString getLogin();
    ~DialogMain();
private:
    QMenu* dbMenu;
    QPushButton *okButt;
    QString dbName;
    QSqlDatabase dbConnect();
    QString pass;
    QString login;
    void createAction(QMenu* menu,QString name);
public slots:
    void okButtCLicked();
    void dbMenues();
};

#endif // DATASELECT_H
