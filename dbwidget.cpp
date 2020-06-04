#include "Dbwidget.h"


DbWidget::DbWidget(QWidget* pwgt): QMainWindow(pwgt)
{
QVBoxLayout * vLayout = new QVBoxLayout();
QPushButton* addRow = new QPushButton("Add Row");

vLayout->addWidget(addRow);
setLayout(vLayout);
}


