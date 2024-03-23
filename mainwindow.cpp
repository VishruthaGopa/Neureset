#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the date and time label
    initializeDateTimeLabel();

    // Set alternating row colors using stylesheet
    ui->listWidget->setStyleSheet("QListWidget { alternate-background-color: #d3d3d3; }");

    // Connect listWidget's itemClicked signal to handleListItemClicked slot
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::handleListItemClicked);
    connect(ui->menuButton, &QPushButton::clicked, this, &MainWindow::toggleMenuVisibility);

    // menu button connections
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::navigateUpMenu);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::navigateDownMenu);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleListItemClicked(QListWidgetItem *item) {
    QString itemName = item->text();
    if (itemName == "NEW SESSION") {
        qInfo("NEW SESSION");

    } else if (itemName == "SESSION LOG") {
        qInfo("SESSION LOG");

    } else if (itemName == "TIME AND DATE") {
        qInfo("TIME AND DATE");

    }
}

void MainWindow::navigateUpMenu() {
    qInfo("up pressed");

    int currentIndex = ui->listWidget->currentRow();
    int itemCount = ui->listWidget->count();

    if (itemCount == 0) {
        // No items to navigate
        return;
    }

    // If no item is currently selected or the first item is selected,
    // select the last item. Otherwise, select the previous item.
    if (currentIndex <= 0) {
        ui->listWidget->setCurrentRow(itemCount - 1);
    } else {
        ui->listWidget->setCurrentRow(currentIndex - 1);
    }
}

void MainWindow::navigateDownMenu() {
    qInfo("down pressed");

    int currentIndex = ui->listWidget->currentRow();
    int itemCount = ui->listWidget->count();

    if (itemCount == 0) {
        // No items to navigate
        return;
    }

    // If no item is currently selected or the last item is selected,
    // select the first item. Otherwise, select the next item.
    if (currentIndex == -1 || currentIndex == itemCount - 1) {
        ui->listWidget->setCurrentRow(0);
    } else {
        ui->listWidget->setCurrentRow(currentIndex + 1);
    }
}

void MainWindow::initializeDateTimeLabel() {
    // Show the current date and time in the QLabel
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("MMM dd yyyy, hh:mm:ss");
    ui->listWidget->addItem(dateTimeString);
}

void MainWindow::toggleMenuVisibility() {
    // Clear the listWidget contents in any case
    ui->listWidget->clear();
    
    if (!showMenuOptions) {
        // Show the three menu options
        ui->listWidget->addItem("NEW SESSION");
        ui->listWidget->addItem("SESSION LOG");
        ui->listWidget->addItem("TIME AND DATE");
    } else {
        // Show the current date and time
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateTimeString = currentDateTime.toString("MMM dd yyyy, hh:mm:ss");
        ui->listWidget->addItem(dateTimeString);
    }

    // Toggle the flag for the next call
    showMenuOptions = !showMenuOptions;
}
