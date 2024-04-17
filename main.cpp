#include "mainwindow.h"
#include "neuresetdevice.h"
#include "eegheadset.h"
#include "sliderwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
