#include "pcwindow.h"
#include "ui_pcwindow.h"
#include <QtDebug>

PCWindow::PCWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PCWindow)
{
    ui->setupUi(this);

    // instantiate pc
    pc = new PC();

    // create table model view
    setUpTable();

    // testing with adding values
    connect(ui->exampleButton, SIGNAL(released()), this, SLOT(handleExample()) );

    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(handleConnect()));

}

PCWindow::~PCWindow() { delete ui; }

void PCWindow::setUpTable(){

    // bind to table view
    ui->table->setModel(&model);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void PCWindow::handleConnect(){
    if( pc->getConnect() == false ){ pc->setConnect(true); }
    else{ pc->setConnect( false ); }
}

void PCWindow::handleExample(){
    qInfo("Add new row!");

    // prepends to the front
//    int a = model.rowCount(QModelIndex());

    // appends to the back
    int a = model.rowCount();

    model.insertRows(a, 1, QModelIndex());

}

