#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    db = QSqlDatabase::addDatabase("QPSQL");
    bool connect = isConnect(db,"127.0.0.1","test","postgres","2426");
    if(!connect){
        qDebug()<<db.lastError().text();
        return;
    }else qDebug()<<"Success\n";



}

MainWindow::~MainWindow()
{
}
bool MainWindow::isConnect(QSqlDatabase &localDB, QString host, QString dbName, QString userName, QString pass){

    bool conn = false;
    localDB.setUserName(userName);
    localDB.setPassword(pass);
    localDB.setHostName(host);
    localDB.setDatabaseName(dbName);
    if(!localDB.open());
    else conn = true;
    return conn;
}


