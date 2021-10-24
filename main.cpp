#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>

#include "latextjs.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("asd");
    a.setApplicationName("qmathjax_test");
//    LatextJs l;

        MainWindow w;
        w.show();

    return a.exec();
}
