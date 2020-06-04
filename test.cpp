#include "test.h"
#include <vector>




Test::Test(QWidget* widget)
    :QWidget(widget)
{


    DialogMain dialog;

    dialog.setModal(true);
    dialog.resize(100,100);
    dialog.exec();
    dbName = dialog.getDataName();
    //connect
    //if(dbName.isEmpty())
    login = dialog.getLogin();
    password = dialog.getPass();
    db = dbConnect();
    db.setDatabaseName(dbName);


    if(!db.open()){
        qDebug()<<db.lastError().text();
        return;
    }
    else
        qDebug()<<"Success\n";




// creating LAYOUTS...

    QHBoxLayout* hLayout = new QHBoxLayout();
    QHBoxLayout* hLayout2 = new QHBoxLayout();
    QVBoxLayout* lay_Center = new QVBoxLayout();
    QVBoxLayout* vLayout= new QVBoxLayout();
    QVBoxLayout* vLayout2= new QVBoxLayout();
    QVBoxLayout* vLayout3 = new QVBoxLayout();
//    MainLayout
    QVBoxLayout* mainLayout = new QVBoxLayout();

//    Menu and other BUTTONS and WIDGETS FOR GUI
    cmd = new QPushButton();
    menu = new QMenu(cmd);
    QStringList list = db.tables();
    for(int i =0; i<list.size();i++)
    createAction(menu,list[i]);
    cmd->setText(list[0]);
    cmd->setMenu(menu);
    {
    model = new QSqlRelationalTableModel(this,db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable(list[0]);
    model->select();
    }
    cmd2 = new QPushButton();
    menu2 = new QMenu(cmd2);

    QSqlQuery checkQuery;
        checkQuery.exec("select name from client;");
        while(checkQuery.next()){
            QString str = checkQuery.value(0).toString();
            namesLst<<str;
        }   if(!namesLst.isEmpty()){
//            qDebug()<<namesLst;
            for(int i=0;i<namesLst.size();i++){
                QAction* setTable = new QAction(namesLst[i]);
                connect(setTable,SIGNAL(triggered()), SLOT(clientNamesAction()));
                menu2->addAction(setTable);
            }

            cmd2->setText("Select Client");
            cmd2->setMenu(menu2);
        }

            else cmd2->setText(" ");
        checkQuery.exec("select id from client;");
        while(checkQuery.next()){
            QString str = checkQuery.value(0).toString();
            idLst<<str;
        }



    QPushButton* addRow = new QPushButton("Add Row");
    QPushButton* deleteRow = new QPushButton("Delete Row");

    QPushButton* submit = new QPushButton("Submit");
    QPushButton* select = new QPushButton("Select");
    QPushButton* revert = new QPushButton("Revert");

    QToolBar *bar = new QToolBar();

    table = new QTableView();
    command = new QLineEdit();
    QPushButton * ok = new QPushButton("OK");

    //RadioButtons and GroupBox
    group = new QGroupBox("Type");
    standart = new QRadioButton("Standart");
    innerJoin = new QRadioButton("Inner Join");
//    leftJoin = new QRadioButton("Left Join");
    standart->setChecked(true);

    //bar
    bar->addAction("Main Window");


    //LEFT MENU LAYOUT

    vLayout->addWidget(addRow,1);
    vLayout->addWidget(deleteRow,2);
    vLayout->addWidget(cmd2);


    vLayout->addStretch(1);
    vLayout->addWidget(standart);
    vLayout->addWidget(innerJoin);
//    vLayout->addWidget(leftJoin);

    //BOTTOM MENU ROW AND BUTTON "OK"
    vLayout3->addWidget(command);
    vLayout3->addWidget(ok);
    //ADD BOTTOM MENU IN HORISONTAL LAYOUT
    hLayout2->addLayout(vLayout3);
    hLayout2->addWidget(cmd);

    //CENTER LAYOUT ADD TABLE AND LAYOUT WITH BOTTOM MENU
    lay_Center->addWidget(table);
    lay_Center->addLayout(hLayout2);

    //temporary space
    int* space = new int(14);

    //RIGHT MENU LAYOUT
    vLayout2->addWidget(submit,1);
    vLayout2->addSpacing(*space);
    vLayout2->addWidget(select,2);
    vLayout2->addSpacing(*space);
    vLayout2->addWidget(revert,3);
    vLayout2->addStretch(1);

    delete space;

    //CREATING ONE LAYOUT WHICH HAVE ALL MENU
    hLayout->addLayout(vLayout);
    hLayout->addLayout(lay_Center);
    hLayout->addLayout(vLayout2);

    //MAIN LAYOUT WHICH HAVE HORISONTAL MENU AND TOOL BAR
    mainLayout->addWidget(bar);
//    mainLayout->addWidget(cmd2);
    mainLayout->addLayout(hLayout);

    //SET MAIN LAYOUT
    setLayout(mainLayout);
    //SET DATABASE MODEL FOR VIEW
    table->setModel(model);
    //CONNECTS
    connect (addRow, SIGNAL(clicked()), SLOT(addRowButtonClicked()));
    connect (deleteRow, SIGNAL(clicked()), SLOT(deleteRowButtonClicked()));
    connect (submit, SIGNAL(clicked()), SLOT(submitButtonClicked()));
    connect (select, SIGNAL(clicked()), SLOT(selectButtonClicked()));
    connect (revert, SIGNAL(clicked()), SLOT(revertButtonClicked()));
    connect (ok, SIGNAL(clicked()), SLOT(okButtonClicked()));
    connect (cmd, SIGNAL(clicked()), SLOT (MenuTableSelected()));



}


void Test::addRowButtonClicked(){

qDebug()<<"Inserting Row";
model->insertRow(model->rowCount());

}
void Test::deleteRowButtonClicked(){
    int selectRow = table->currentIndex().row();
    if(selectRow >=0) model->removeRow(selectRow);
    else qDebug()<<"no row Selected";

}
void Test::submitButtonClicked(){
    model->submitAll();

}
void Test::selectButtonClicked(){
    model->select();
    cmd2->setText("Select Client");

}
void Test::revertButtonClicked(){
    model->revertAll();
}
void Test::okButtonClicked(){
    QString str= command->text();
        if(standart->isChecked()){
        QStringList lst;
        lst<<str.split(" ");

        if(lst[0]=="set"){
            QString buffer;
            if(lst[lst.size()-1][lst[lst.size()-1].size()-1] == ';'){
            for(int i = 0;i<lst[lst.size()-1].size()-1;i++){
                buffer +=lst[lst.size()-1][i];
                }
            lst[lst.size()-1] = buffer;
            }
            model->setTable(lst[1]);
            model->select();
            table->setModel(model);
        }
        else{

            QSqlQueryModel* query1 = new QSqlQueryModel();
            query1->setQuery(str);

            if(lst[0] == "select" || lst[0] =="select*"){
                table->setModel(query1);
                cmd2->setText("Select Client");
            }

        }
    }else if(innerJoin->isChecked()){
            QStringList lst;
            lst<<str.split(" ");
            QSqlQueryModel* query1 = new QSqlQueryModel();
            QString query = queryInnerSearch(lst);
             query1->setQuery(query);
            table->setModel(query1);
            //qDebug()<<lst;
        }
//     else if(leftJoin->isChecked()){}
}
void Test::MenuTableSelected(){
    cmd2->setText("Select Client");
    if(standart->isChecked()){
    QString str = ((QAction*) sender()) ->text();
    cmd->setText(str);
    model->setTable(str);
    model->select();
    table->setModel(model);

    }
}
void Test::createAction(QMenu* menu,QString name){

    QAction* setTable = new QAction(name);
    connect (setTable,SIGNAL(triggered()),SLOT(MenuTableSelected()));
    menu->addAction(setTable);
}
QString Test::queryInnerSearch(QStringList &lst){
    QStringList newList;
    QString queryRow = "select ";
    int counter=0;
    for(int i=0;i<lst.size();i++){
       newList<<lst[i].toLower();
       if(newList[i] == "output" || newList[i]=="from" || newList[i]=="on") counter++;
    }
    if(counter == 3){
        cmd2->setText("Select Client");
        for(int i=1;i<newList.size();i++){
            while(newList[i]!= "from"){
                queryRow+=newList[i];
                if(newList[i+1] == "as") queryRow+=" ";
                if(newList[i] == "as"){
                queryRow+=" ";
                i++;
                queryRow+=newList[i];
                queryRow+=" ";
                }
                if(newList[i+1]!= "from" && newList[i+1] != "as")
                    queryRow+=", ";

                 i++;
            }
            queryRow+=" ";
            queryRow += newList[i];
            i++;
            queryRow+=" ";
            QStringList tables;
            while(newList[i]!= "on"){
                tables<<newList[i];
                i++;
            }
            queryRow+= tables[0];
            i++;

            // ITEM queryRow+=newList[i];

            for(int j=1;j<tables.size();j++){
                queryRow+=" Inner Join ";
                queryRow+=tables[j];
                //if(sz%2 != 0) qDebug()<<"Incorrect relation";
                queryRow+=" on ";
                queryRow+=newList[i];
                i++;
                queryRow+=" = ";
                queryRow+=newList[i];
                i++;

                }
            }

    }
    else qDebug()<<"Incorrect Query";
return queryRow;
}
QSqlDatabase Test::dbConnect(){
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//        db.setDatabaseName(dbName);
        db.setHostName("127.0.0.1");
        db.setUserName(login);
        db.setPassword(password);
        db.open();
        return db;
    }
}
void Test::setPass(QString pas){
    password = pas;

}
void Test::setLogin(QString log){
    login = log;

}

void Test::clientNamesAction(){
    if(standart->isChecked()){
    QString str = ((QAction*) sender())->text();
    cmd2->setText(str);
    QString id;
    for(int i =0;i<namesLst.size();i++){
        if(str == namesLst[i]) id = idLst[i];
    }
    QSqlQueryModel* query1 = new QSqlQueryModel();
    QString query = "select client.name, item.name, relation.kolvo, item.price, client.phone from item inner join relation on item.id = relation.id_it inner join client on relation.id_cl = client.id where id_cl ="+id+";";
     query1->setQuery(query);
    table->setModel(query1);

    }
}
Test::~Test(){

}
