/*
 * (c)2014 James Hudson - www.disconnectionist.com
 * Released under GPL v2.0
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
