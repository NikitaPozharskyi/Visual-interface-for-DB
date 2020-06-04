#include "dataselect.h"
#include <QDialog>
DialogMain::DialogMain(QWidget *parent)
    : QDialog(parent)
{
    Authorization auth;
    auth.setModal(true);
    auth.resize(200,200);
    auth.exec();
    pass = auth.getPass();
    login = auth.getLogin();
   { QVBoxLayout* mainLayout = new QVBoxLayout();
    QSqlDatabase db2 = dbConnect();
    okButt = new QPushButton("Choose");
    QStringList dbList;
    dbButt = new QPushButton("postgres");
    QMenu * menu2 = new QMenu(dbButt);

    {QSqlQuery checkQuery;
    checkQuery.exec("Select* from pg_database;");
    while(checkQuery.next()){
        QString str = checkQuery.value(0).toString();
        dbList<<str;
    }}
//    qDebug()<<dbList;
    for(int i=0;i<dbList.size();i++){
        QAction* setTable = new QAction(dbList[i]);
        connect(setTable,SIGNAL(triggered()), SLOT(dbMenues()));
        menu2->addAction(setTable);
    }
    dbButt->setMenu(menu2);
    mainLayout->addWidget(dbButt);
    mainLayout->addWidget(okButt);

    setLayout(mainLayout);
    connect(okButt, SIGNAL(clicked()), SLOT(okButtCLicked()));
    db2.close();}

}

QSqlDatabase DialogMain::dbConnect(){
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//        db.setDatabaseName(dbName);
        db.setHostName("127.0.0.1");
        db.setUserName(login);
        db.setPassword(pass);
        db.open();
        return db;
    }
}
void DialogMain::okButtCLicked(){

    dbName =  dbButt->text();
    close();
}
QString DialogMain::getDataName(){

    return dbName;
}
void DialogMain::dbMenues(){
    QString str = ((QAction*) sender())->text();
    dbButt->setText(str);

}
QString DialogMain::getPass(){
    return pass;

}
QString DialogMain::getLogin(){
    return login;

}
DialogMain::~DialogMain(){


}
