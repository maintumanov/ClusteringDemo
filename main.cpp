#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator appTranslator;
    QCoreApplication::setOrganizationName(QLatin1String("VyatSU"));
    QCoreApplication::setApplicationName(QLatin1String("ClusteringDemo"));
    QCoreApplication::setApplicationVersion("0.1.1.1");
    appTranslator.load(QLatin1String("cldemo_")+QLocale::system().name(),"://");
    a.installTranslator(&appTranslator);
    MainWindow w;
    w.show();

    return a.exec();
}
