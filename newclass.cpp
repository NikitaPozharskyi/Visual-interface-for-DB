#include "newclass.h"

newClass::newClass(QWidget* parent) : QMainWindow(parent)
{
    QVBoxLayout * vLayout = new QVBoxLayout();
    QPushButton* addRow = new QPushButton("Add Row");

    vLayout->addWidget(addRow);
    setLayout(vLayout);
    arent->show();
}
newClass::~newClass(){

}
