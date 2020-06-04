#ifndef NEWCLASS_H
#define NEWCLASS_H

#include <QMainWindow>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRelationalTableModel>

#include <QWidget>
#include <QStack>
#include <QBoxLayout>
#include <QtWidgets>
class newClass: public QMainWindow
{
    Q_OBJECT
public:
    newClass(QWidget* parent = nullptr);
    ~newClass();
private:
    QSqlDatabase db;
    QSqlRelationalTableModel * model;

};

#endif // NEWCLASS_H
