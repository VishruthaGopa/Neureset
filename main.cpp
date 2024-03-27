#include "mainwindow.h"
#include "neuresetdevice.h"
#include "eegheadset.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    EEGHeadset *eegheadset=new EEGHeadset();
    NeuresetDevice neureset(eegheadset);

    return a.exec();
}
