#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("din-a-testware");
    QCoreApplication::setOrganizationDomain("din-a-testware.de");
    QCoreApplication::setApplicationName("Replicator Remote Control");

    MainWindow w;
    //w.show();
    w.showFullScreen();


    return a.exec();
}
