#ifndef DBWIDGET_H
#define DBWIDGET_H
#include <QWidget>
#include <QStack>
#include <QBoxLayout>
#include <QtWidgets>

class QPushButton;

class DbWidget :public QMainWindow{
    Q_OBJECT
public:
    DbWidget();
    ~DbWidget();
private:

//    QPushButton* createButton(const QString & str);
    DbWidget(QWidget* pwgt = nullptr);



public slots:
//    void slotButtonClicked();
};

#endif // DBWIDGET_H
