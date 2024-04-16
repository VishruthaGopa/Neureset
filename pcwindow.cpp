#include "pcwindow.h"
#include "ui_pcwindow.h"
#include "transferwindow.h"
#include <QtDebug>

PCWindow::PCWindow(NeuresetDevice* nd, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PCWindow)
{
    ui->setupUi(this);

    // instantiate pc
    pc = new PC(nd);

    // create table model view
    setUpTable();

    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(handleConnect()));
    connect(ui->transferButton, SIGNAL(released()), this, SLOT(handleTransfer()));

}

PCWindow::~PCWindow() { delete ui; }

void PCWindow::setUpTable(){

    // bind to table view
    ui->table->setModel(&model);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void PCWindow::handleConnect(){
    if( pc->getConnect() == false ) {
        pc->setConnect(true);
        ui->transferButton->setEnabled(true);
    }
    else {
        pc->setConnect(false);
        ui->transferButton->setEnabled(false);
    }
}

void PCWindow::handleTransfer() {

    // this grabs from neureset device
    // pc->retrieveSessions();

    // test
//    Session* s = new Session();
//    Session* s2 = new Session();
//    s->startTimer();
//    s->endTimer();
//    s->setBeforeBaseline(69);
//    s->setAfterBaseline(420);
//    s2->startTimer();
//    s2->endTimer();
//    s2->setBeforeBaseline(727);
//    s2->setAfterBaseline(727);
//    QList<Session*> list;
//    list.append(s);
//    list.append(s2);
//    pc->retrieveSessions(&list);
    // end hard code
    pc->retrieveSessions();
    TransferWindow* transferWindow = new TransferWindow(this);
    transferWindow->displaySessions(pc->getSessionLogsBuf());
    transferWindow->exec();

    bool r = transferWindow->getResponse();
    if (r) {
        int a = model.rowCount();
        model.insertRows(a, pc->getSessionLogsBuf()->count(), QModelIndex());
        pc->commitToDb();
        qInfo("Done");
    }
    else {
        pc->cancelCommit();
    }

    delete transferWindow;
}

