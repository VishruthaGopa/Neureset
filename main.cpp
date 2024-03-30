#include "pcwindow.h"
#include "datamodel.h"

#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PCWindow w;

//    QTableView tableView;
//    MyModel model;
//    tableView.setModel(&model);
//    tableView.show();

    w.show();
    return a.exec();
}
