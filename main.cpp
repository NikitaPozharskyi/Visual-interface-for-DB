#include "test.h"
#include "dataselect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    dialog->show();
    Test t;


    t.setWindowTitle("Test");

    t.resize(600,400);
    t.show();

    return a.exec();
}

