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

PCWindow::~PCWindow() { 
    delete ui; 
    delete pc;
}

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
    pc->retrieveSessions();
    TransferWindow* transferWindow = new TransferWindow(this);
    transferWindow->displaySessions(pc->getSessionLogsBuf());
    transferWindow->exec();

    bool r = transferWindow->getResponse();
    if (r) {
        int a = model.rowCount();
        int count = pc->getSessionLogsBuf()->count();
        pc->commitToDb();
        model.insertRows(a, count, QModelIndex());
        qInfo("Done");
    }
    else {
        pc->cancelCommit();
    }

    delete transferWindow;
}

