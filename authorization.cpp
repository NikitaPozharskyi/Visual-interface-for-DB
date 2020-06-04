#include "authorization.h"

Authorization::Authorization(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout* mainLay = new QVBoxLayout();
    QHBoxLayout* secondLay = new QHBoxLayout();
    QHBoxLayout* thirdLay = new QHBoxLayout();
    QPushButton* auth = new QPushButton("login");
    log = new QLineEdit();
    pass = new QLineEdit();
    QLabel* first = new QLabel("Login");
    QLabel* second = new QLabel("Password");
    secondLay->addWidget(first);
    secondLay->addWidget(log);
    thirdLay->addWidget(second);
    thirdLay->addWidget(pass);
    mainLay->addLayout(secondLay);
    mainLay->addLayout(thirdLay);
    mainLay->addWidget(auth);



    connect(auth,SIGNAL(clicked()),SLOT(authButtonClicked()));
    setLayout(mainLay);

}
void Authorization::authButtonClicked(){
    QSqlDatabase db2 = dbConnect(log->text(), pass->text());
    if(!db2.open()){
        QMessageBox::critical(this,"authentification error.","Incorrect Login or password.",QMessageBox::Ok);
        exit(0);

    }else{
        isConnect = true;
        close();
    }
    db2.close();
}
QString Authorization::getPass(){return pass->text();}
QString Authorization::getLogin(){return log->text();}
bool Authorization::getConnectInfo(){return isConnect;}
QSqlDatabase Authorization::dbConnect(QString l, QString p){
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("127.0.0.1");
        db.setUserName(l);
        db.setPassword(p);
        db.open();
        return db;
    }
}
Authorization::~Authorization(){}
