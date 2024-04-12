#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    eegheadset=new EEGHeadset();
    neureset=new NeuresetDevice(eegheadset);

    // Device off at start
    powerOn = false;
    deviceOff();
    showDateTimeEditActive = false;
    showTimer = false;

    // Enable the establish contact button
    ui->establishContactButton->setEnabled(true);
    ui->loseContactButton->setEnabled(false);

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

    // Connect batterySlider signal to handleBatteryLevelChanged slot
    connect(ui->batterySlider, &QSlider::sliderReleased, this, &MainWindow::handleBatteryLevelChanged);

    // Connect Power On/Off signal
    connect(ui->onoffButton, &QPushButton::clicked, this, &MainWindow::powerButtonClicked);

    // Set up the displayDateTime
    QTimer *displayDateTime = new QTimer(this);
    connect(displayDateTime, SIGNAL(timeout()), this, SLOT(updateDateTime()));
    displayDateTime->start(1000); // Timer ticks every 1000 milliseconds (1 second)
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
        qInfo("Starting NEW SESSION...");
        onStartButtonClicked();

    } else if (selectedItemText == "SESSION LOG") {
        qInfo("Displaying SESSION LOG...");
        onSessionLogRequested();

    } else if (selectedItemText == "TIME AND DATE") {
        qInfo("Setting TIME AND DATE...");
        showDateTimeEdit();

    }
}

void MainWindow::showDateTimeEdit() {
    // Clear screen of menu choices
    ui->listWidget->clear();

    showDateTimeEditActive = true; 

    //Display date/time edit
    ui->dateTimeEdit->show();

    // Set date and time
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setEnabled(true);
}

void MainWindow::onSessionLogRequested(){
     showMenuOptions = !showMenuOptions;
    //clear screen of menu choices
    ui->listWidget->clear();
    QString sessionDataString;

    for (Session *session : neureset->getSessionLog()->getSessionHistory()) {
        sessionDataString += QString("Start Time: %1, End Time: %2, Before Baseline: %3, After Baseline: %4\n")
                .arg(session->getStartTime().toString())
                .arg(session->getEndTime().toString())
                .arg(session->getBeforeBaseline())
                .arg(session->getAfterBaseline());
    }
    if(sessionDataString.isEmpty()){
        sessionDataString=QString("NO LOGGED SESSIONS");
    }
    //display session data
    ui->listWidget->addItem(sessionDataString);
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

        // Enable the lose contact button
        ui->loseContactButton->setEnabled(true);
        ui->establishContactButton->setEnabled(false);

    } else if (button == ui->loseContactButton) {
        // Logic for losing contact with EEG headset
        qInfo("Losing contact with EEG headset...");
        ui->contactLight->setStyleSheet("background-color: #e4f0fa;"); // dull blue
        ui->contactLostLight->setStyleSheet("background-color: #FF000D;"); // brighter red

        // Enable the establish contact button
        ui->establishContactButton->setEnabled(true);
        ui->loseContactButton->setEnabled(false);

    }
}

void MainWindow::timerLabel() {
    showDateTimeEditActive = false;  
    showTimer = true;

    ui->listWidget->clear();
    QString timeRemaining = ("Time Remaining");
    ui->listWidget->addItem(timeRemaining);
}


void MainWindow::updateDateTime() {
    if (powerOn && showDateTimeEditActive) {
        ui->listWidget->clear();
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateTimeString = currentDateTime.toString("MMM dd yyyy, hh:mm:ss");
        //ui->labelDateTime->setText(dateTimeString);
        ui->listWidget->addItem(dateTimeString);
    }
}


void MainWindow::toggleMenuVisibility() {
    // Clear the listWidget contents in any case
    ui->listWidget->clear();
    ui->dateTimeEdit->hide();

    if (!showMenuOptions) {
        showDateTimeEditActive = false;  

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
        timerLabel();  
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

// handle slider release and retrieve slider value
void MainWindow::handleBatteryLevelChanged() {
    int batteryLevel = ui->batterySlider->value();
    qInfo("Battery Level: %d", batteryLevel);
}

void MainWindow::powerButtonClicked() {
    powerOn = !powerOn; //Toggle powerOn when clicked
    if (powerOn){
        deviceOn();
    }else{
        deviceOff();   
    }
}

void MainWindow::deviceOn(){
    qInfo("Device ON");
    timerLabel();    
    ui->frame->setEnabled(true);
}

void MainWindow::deviceOff(){
    qInfo("Device OFF");
    ui->listWidget->clear();
    ui->dateTimeEdit->hide();
    QString item = "Neureset Device is Off.";
    ui->listWidget->addItem(item);
    ui->frame->setEnabled(false);
}