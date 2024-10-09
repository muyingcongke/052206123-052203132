#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.addPjItem("aaa","bbb");
    w.addPjItem("aaa","bbb");
    w.addPjItem("aaa","bbb");
    w.addPjItem("aaa","bbb");
    w.show();
    return a.exec();
}
