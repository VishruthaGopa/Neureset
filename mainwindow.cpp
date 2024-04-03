#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    eegheadset=new EEGHeadset();
    neureset=new NeuresetDevice(eegheadset);
    // Initialize the date and time label
    initializeDateTimeLabel();

    // Start with dull signal lights
    ui->contactLight->setStyleSheet("background-color: #e4f0fa;"); // dull blue
    ui->treatmentLight->setStyleSheet("background-color: #ddf3c8;"); // dull green
    ui->contactLostLight->setStyleSheet("background-color: #ffcccf;"); // dull red
    ui->progressBar->setValue(0);

    // Connect listWidget's itemClicked signal to handleListItemClicked slot
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::handleSelection);
    connect(ui->menuButton, &QPushButton::clicked, this, &MainWindow::toggleMenuVisibility);

    connect(ui->okButton, &QPushButton::clicked, this, &MainWindow::handleSelection);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseButtonClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStopButtonClicked);

    // Menu button connections
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::navigateUpMenu);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::navigateDownMenu);

    // Connect EEG headset panel buttons
    connect(ui->establishContactButton, &QPushButton::clicked, this, &MainWindow::handleEEGHeadsetPanel);
    connect(ui->loseContactButton, &QPushButton::clicked, this, &MainWindow::handleEEGHeadsetPanel);

    connect(neureset,&NeuresetDevice::sessionProgress,this,&MainWindow::updateProgress);


}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::handleSelection() {
    // Get the currently selected item
    QListWidgetItem* currentItem = ui->listWidget->currentItem();
    if (!currentItem) {
        qInfo("No item selected");
        return;
    }

    QString selectedItemText = currentItem->text();

    // Act based on the text of the currently selected item
    if (selectedItemText == "NEW SESSION") {
        // Logic for starting a new session
        qInfo("Starting NEW SESSION...");
        onStartButtonClicked();
    } else if (selectedItemText == "SESSION LOG") {
        // Logic for showing session log
        qInfo("Opening SESSION LOG...");
    } else if (selectedItemText == "TIME AND DATE") {
        // Logic for showing time and date info
        qInfo("Showing TIME AND DATE...");
    }
}


void MainWindow::onStartButtonClicked() {
    // Starting a new session or resuming
    qInfo("Session started/resume");
    ui->contactLight->setStyleSheet("background-color: #2784D6;"); // brighter blue
    ui->contactLostLight->setStyleSheet("background-color: #ffcccf;"); // dull red
    neureset->startSession();
    //greenTreatmentSignal(); //just testing here
}

void MainWindow::greenTreatmentSignal() {
    ui->treatmentLight->setStyleSheet("background-color: #60B115;"); // brighter green
}


void MainWindow::onPauseButtonClicked() {
    // pause session
    qInfo("Session paused");
    neureset->pauseSession();
}

void MainWindow::onStopButtonClicked() {
    // Stop and possibly reset the session
    qInfo("Session stopped");
}


void MainWindow::handleEEGHeadsetPanel() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (button == ui->establishContactButton) {
        // Logic for establishing contact with EEG headset
        qInfo("Establishing contact with EEG headset...");
        onStartButtonClicked();

    } else if (button == ui->loseContactButton) {
        // Logic for losing contact with EEG headset
        qInfo("Losing contact with EEG headset...");
        ui->contactLight->setStyleSheet("background-color: #e4f0fa;"); // dull blue
        ui->contactLostLight->setStyleSheet("background-color: #FF000D;"); // brighter red

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
        // Define alternating colors
        QColor color1(235, 235, 235); // Light gray
        QColor color2(215, 215, 215); // Slightly darker gray

        // Show the three menu options with alternating colors
        QStringList options = {"NEW SESSION", "SESSION LOG", "TIME AND DATE"};
        for (int i = 0; i < options.size(); ++i) {
            QListWidgetItem *item = new QListWidgetItem(options[i]);
            item->setBackground((i % 2 == 0) ? color1 : color2);
            ui->listWidget->addItem(item);
        }

    } else {
        // Show the current date and time
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateTimeString = currentDateTime.toString("MMM dd yyyy, hh:mm:ss");
        ui->listWidget->addItem(dateTimeString);
    }

    // Toggle the flag for the next call
    showMenuOptions = !showMenuOptions;
}

void MainWindow::updateProgress(int progress){
    ui->progressBar->setValue(progress);
    // If percentage reaches 100%, change the background color to light green and font color to white
    if (progress == 100) {
        ui->progressBar->setStyleSheet("QProgressBar { background-color: lightgreen; color: white;text-align: center; }"
                                    "QProgressBar::chunk { background-color: green; text-align: center; }");
    } else {
        // Reset the stylesheet to default if the progress is not 100%
        ui->progressBar->setStyleSheet("");
    }





}
