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
    batteryDied = false;
    showDateTimeEditActive = false;
    showTimer = false;
    ui->batterySlider->setValue(100);


    // Set date and time
    updatedDateTime = QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(updatedDateTime);
    ui->updateDateTimeButton->hide();


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

    // Connect the clicked signal of the updateDateTimeButton to the slot
    connect(ui->updateDateTimeButton, &QPushButton::clicked, this, &MainWindow::updateDateTimeButtonClicked);

    // Connect greenTreatmentSignal slot
    //connect(eegheadset, &EEGHeadset::treatmentAppliedSignal, this, &MainWindow::greenTreatmentSignal);
    connect(neureset, &NeuresetDevice::treatmentAppliedSignal, this, &MainWindow::greenTreatmentSignal);

    // Connect uploadPCButton and showWaveformButton signal
    connect(ui->uploadPCButton, &QPushButton::clicked, this, &MainWindow::uploadPCButtonClicked);
    connect(ui->showWaveformButton, &QPushButton::clicked, this, &MainWindow::showWaveformButtonClicked);

    // Set up the QTimer to update updatedDateTime every second
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        updatedDateTime = updatedDateTime.addSecs(1);
        // Update the date/time in NeuresetDevice
        //neureset->setCurrentDateTime(updatedDateTime);
    });
    timer->start(1000); //updatedDateTime var changes every 1 second

    // Set up the displayDateTime
    QTimer *displayDateTime = new QTimer(this);
    connect(displayDateTime, SIGNAL(timeout()), this, SLOT(updateDateTime()));
    displayDateTime->start(1000); // Display updates every 1 second

    // Set up the QTimer to check battery level periodically
    QTimer *batteryCheckTimer = new QTimer(this);
    connect(batteryCheckTimer, &QTimer::timeout, this, &MainWindow::checkBatteryLevel);
    batteryCheckTimer->start(1000); // Check battery level every 5 seconds

    // Initialize sessionTimer
    sessionTimer = new QTimer(this);

    // Set up the countdownTimer
    QTimer *countdownTimer = new QTimer(this);
    connect(countdownTimer, SIGNAL(timeout()), this, SLOT(updateTimerLabel()));
    countdownTimer->start(500); // Display updates every half second

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkBatteryLevel() {
    int batteryLevel = ui->batterySlider->value();
    if (batteryLevel <= 0) {
        powerOn = false;
        batteryDied = true;
        qInfo("Battery Level: %d", batteryLevel);
        onStopButtonClicked(); // End Session if battery dies

        deviceOff();
        QString item = "Battery died.";
        ui->listWidget->addItem(item);
    }else if(batteryDied && batteryLevel>=0) {
        powerOn = true;
        deviceOn();
        //qInfo("Battery Level: %d", batteryLevel);
        batteryDied = false;
    }

    QString sliderStyle = "groove:horizontal { border: 5px solid #5c5c5c; border-radius: 10px; height: 1px; margin: 2px 0; }"; // change the horizontal groove with rounded corners
    sliderStyle += "QSlider::sub-page:horizontal { background: green; border: 1px solid #d4d4d4; border-radius: 10px; }"; // color for the left side of the handle with border and rounded corners
    sliderStyle += "QSlider::add-page:horizontal { background: #ECECEC; border: 1px solid #d4d4d4; border-radius: 10px; }"; // color for the right side of the handle with border and rounded corners
    sliderStyle += "QSlider::handle:horizontal { background: white; border: 0.5px solid #5c5c5c; width: 6px; height: 6px; margin: -3px 0; border-radius: 3px; }";


    // Change green to red if battery level is less than or equal to 15
    if (batteryLevel <= 15) {
        sliderStyle.replace("background: green", "background: red");
    }

    ui->batterySlider->setStyleSheet(sliderStyle);

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
    ui->updateDateTimeButton->show(); //Button to update 

    // Set date and time
    ui->dateTimeEdit->setDateTime(updatedDateTime);
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

void MainWindow::greenTreatmentSignal() {
    // Set the treatment light to bright green
    ui->treatmentLight->setStyleSheet("background-color: #60B115;"); // brighter green
    
    // QTimer to toggle back to dull green after one second
    QTimer::singleShot(1000, this, [=]() {
        ui->treatmentLight->setStyleSheet("background-color: #ddf3c8;"); // dull green
    });
    
    // Reduce battery levels by 10 every stage (40% every session depletion)
    // depletion from 100 to 0 after 2 session -> (40*4)*3
    int currentBatteryLevel = ui->batterySlider->value();
    qInfo("Battery Level: %d", currentBatteryLevel);
    int newBatteryLevel = currentBatteryLevel - 10;
    ui->batterySlider->setValue(newBatteryLevel);

    // Check if the new battery level is <= 0, then turn off the device
    /*if (newBatteryLevel <= 0) {
        deviceOff();
        QString item = "Check battery.";        
        ui->listWidget->addItem(item);
    }*/

}

void MainWindow::onStartButtonClicked() {
    // Starting a new session or resuming

    ui->contactLight->setStyleSheet("background-color: #2784D6;"); // brighter blue
    ui->contactLostLight->setStyleSheet("background-color: #ffcccf;"); // dull red
    
    // Check if session if no session is in progress
    if (!neureset->isSessionInProgress()) {
        qInfo("Session started");

        // Start session timer for 29 seconds
        sessionTimer->start(totalDuration);
        
    }else if(neureset->isSessionPaused()){
        qInfo("Session resumed");
        sessionTimer->start(remainingTime); // Resume the timer from where it left off

    }

    neureset->startSession();

}

void MainWindow::onPauseButtonClicked() {
    // pause session
    if (neureset->isSessionInProgress()) {
        qInfo("Session paused");
        // Save remaining time after pause
        remainingTime = sessionTimer->remainingTime();
        qInfo("Remaining Time after pause: %d", remainingTime);

        sessionTimer->stop(); // Stop the timer when the session is paused.
        qInfo("after pause: %d", remainingTime);

        // qInfo("Paused Time: %d", sessionTimer->remainingTime()); // inactive timer so -1

    }

    neureset->pauseSession();
}

void MainWindow::onStopButtonClicked() {
    // Stop the session
    if (neureset->isSessionInProgress()) {
        qInfo("Session ended");
        neureset->endSession();

        remainingTime = 0;
        sessionTimer->stop(); // Stop the timer.

        ui->listWidget->clear();
        ui->listWidget->addItem("Session ended.");
    }else{
        qInfo("No Session in Progress");
    }

    ui->progressBar->setValue(0);

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
    QString timeRemaining = ("Timer for Session");
    ui->listWidget->addItem(timeRemaining);
}

void MainWindow::updateTimerLabel() {
    if (powerOn && showTimer && neureset->isSessionInProgress()){  
        //qInfo("updateTimerLabel");
        //qInfo("Paused? %s", neureset->isSessionPaused() ? "true" : "false");

        ui->listWidget->clear();
        QString timeRemainingStr;      
        //QString timeRemaining = QString("Time Remaining: %1 seconds").arg(remainingTimeSec);

        // Check if the session is paused
        if (!neureset->isSessionPaused()){
            // Session is not paused, update remaining time normally
            
            // Get remaining time in milliseconds
            int remainingTimeMs = sessionTimer->remainingTime();
            int remainingTimeSec = remainingTimeMs / 1000;

            // Convert milliseconds to seconds
            timeRemainingStr = QString("Time Remaining: %1 seconds").arg(remainingTimeSec);

        }else{
            // Session is paused, use previously calculated remainingTime
            //qInfo("Paused time: %d", remainingTime);

            // Update the timer label with the remaining seconds at paused
            timeRemainingStr = QString("Time Remaining: %1 seconds").arg((remainingTime / 1000));
            ui->listWidget->addItem("Session paused.");

        }

        ui->listWidget->addItem(timeRemainingStr);
    }
}


void MainWindow::updateDateTime() {
    if (powerOn && showDateTimeEditActive) {
        ui->listWidget->clear();
        QString dateTimeString = updatedDateTime.toString("MMM dd yyyy, hh:mm:ss");
        //ui->labelDateTime->setText(dateTimeString);
        ui->listWidget->addItem(dateTimeString);
    }
}

void MainWindow::updateDateTimeButtonClicked() {
    // Update updatedDateTime to reflect changes made by the user in the dateTimeEdit widget
    updatedDateTime = ui->dateTimeEdit->dateTime();
    QString dateTimeString = updatedDateTime.toString("MMM dd yyyy, hh:mm:ss");
    
    // Print the updated date and time
    qInfo("Updated Date Time: %s", qPrintable(dateTimeString));

}



void MainWindow::toggleMenuVisibility() {
    // Clear the listWidget contents
    ui->listWidget->clear();
    ui->dateTimeEdit->hide();
    ui->updateDateTimeButton->hide();
    if (!showMenuOptions) {
        showDateTimeEditActive = false;  
        showTimer = false;

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

void MainWindow::uploadPCButtonClicked() {
    qInfo("Upload Data to PC");
}

void MainWindow::showWaveformButtonClicked() {
    qInfo("Show Waveform");
}
