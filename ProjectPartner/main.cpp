#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    //Project project;
    //project.setData("aaa","bbb","ccc","ddd");
    //w.addPjItem(project);
    w.init();
    //QString str1 = QString("project");//+simua+account+project+user
    //w.createTable(str1);
    //w.insertUserAccount(QString("112234455"),QString("database1"));
    w.queryAllUser();
    w.show();
    return a.exec();
}
