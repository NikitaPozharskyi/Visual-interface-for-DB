#ifndef TEST_H
#define TEST_H
#include <QtWidgets>
#include <QPushButton>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDialog>
#include "dataselect.h"
#include "authorization.h"
class QPushButton;

class Test : public QWidget
{
    Q_OBJECT
public:
    Test(QWidget* widget = nullptr);
    void createAction(QMenu* menu,QString name);
//    void createActionForData(QMenu* menu,QString name);
    QString queryInnerSearch(QStringList& lst);
    QSqlDatabase dbConnect();
    void setPass(QString pas);
    void setLogin(QString log);
    QString dbName; // dbName;

    ~Test();


public slots:
    void addRowButtonClicked();
    void deleteRowButtonClicked();
//    void innerJoinButtonClicked();
//    void leftJoinButtonClicked();


    void submitButtonClicked();
    void selectButtonClicked();
    void revertButtonClicked();
    void okButtonClicked();
    void clientNamesAction();
    void MenuTableSelected();
//    void MenuDatabaseSelected();

private:
    QTableView *table;
    QLineEdit* command;
    QSqlDatabase db;
    QSqlRelationalTableModel* model;
    QGroupBox * group;
    QRadioButton* standart;
    QRadioButton* innerJoin;
//    QRadioButton* leftJoin;
    QPushButton* cmd;
    QPushButton* cmd2;
    QMenu * menu, *menu2;
    QStringList dbList;
    QStringList namesLst;
    QStringList idLst;
    QString password, login;


};

#endif // TEST_H
