#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRelationalTableModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isConnect(QSqlDatabase& localDB, QString host, QString dbName, QString userName, QString pass);

private:
    QSqlDatabase db;
    QSqlRelationalTableModel * model;

};
#endif // MAINWINDOW_H
