// neuresetdevice.cpp
#include "neuresetdevice.h"

NeuresetDevice::NeuresetDevice(EEGHeadset* headset, QObject* parent) : QObject(parent), sessionInProgress(false), stage(0){
    pauseTimer = new QTimer(this);
    QObject::connect(pauseTimer, &QTimer::timeout, this, &NeuresetDevice::pauseTimerOver);

    sessionLog = new SessionLog();
    eegHeadset = headset;
    QObject::connect(eegHeadset, &EEGHeadset::measurementCompleted, this, &NeuresetDevice::measurementHandler);
    QObject::connect(eegHeadset, &EEGHeadset::treatmentCompleted, this, &NeuresetDevice::treatNextHandler);
    QObject::connect(eegHeadset, &EEGHeadset::newSession, this, &NeuresetDevice::gotNewSession);

    percentage = 0;
    totalEvents = 29;
    currEvents = 0;
}

void NeuresetDevice::calculateOverallBaseline() {
    eegHeadset->startMeasurement();
}

void NeuresetDevice::stopTreatment() {

}

void NeuresetDevice::gotNewSession(Session* session, QDateTime &mainwindowDateTime) {
    session->endTimer(mainwindowDateTime);
    sessionLog->addSession(session);
}

void NeuresetDevice::startSession() {
    emit sessionProgress(percentage);
    if (!sessionInProgress) {
        sessionInProgress = true;
        eegHeadset->startSession();
        qInfo("Finding Initial Overall Baseline");
        calculateOverallBaseline();
        stage++;

    } else {
        resumeSession();
    }
}

void NeuresetDevice::measurementHandler(){
    currEvents+=5;
    percentage = (currEvents * 100) / totalEvents;
    emit sessionProgress(percentage);
    if (sessionInProgress) {
        if (stage == 1) {
            eegHeadset->startTreatment(5.0);
            stage++;
        }
        else if (stage == 2) {
            eegHeadset->startTreatment(10.0);
            stage++;
        }
        else if (stage == 3) {
            eegHeadset->startTreatment(15.0);
            stage++;
        }
        else if (stage == 4) {
            eegHeadset->startTreatment(20.0);
            stage++;
        }
        else{
            endSession();
            return;
        }
    }
}

void NeuresetDevice::treatNextHandler(double frequency) {
    currEvents+=1;
    percentage = (currEvents * 100) / totalEvents;
    emit sessionProgress(percentage);
    // Flashing green signal here
    emit treatmentAppliedSignal(); // check placement
    if (sessionInProgress) {
        qInfo("Finding Overall Baseline after %g",frequency);
        calculateOverallBaseline();
    }
}


void NeuresetDevice::endSession() {
    if (sessionInProgress) {
        sessionInProgress = false;
        stage = 0;
        percentage = 0;
        currEvents = 0;
        stopTreatment();

    }
    else {
        qInfo("No Session in Progress");
    }
}

void NeuresetDevice::pauseSession() {
    if (sessionInProgress) {
        eegHeadset->pauseSession();
        sessionPaused = true;
        
        //pauseTimer->start(30000); // Testing with shorter time
        pauseTimer->start(300000); // Five minutes on the clock (300000 ms)
    }
    else {
        qInfo("No session in progress");
    }
}

void NeuresetDevice::resumeSession() {
    if (sessionInProgress) {
        pauseTimer->stop();
        sessionPaused = false;
        eegHeadset->resumeSession();
    }
    else {
        qInfo("No Session in Progress");
    }
}

void NeuresetDevice::cancelSession() {
    if (sessionInProgress) {
        eegHeadset->cancelSession();
        pauseTimer->stop();
        sessionInProgress = false;
        percentage = 0;
        sessionPaused = false;
        emit sessionProgress(percentage);
    }
    else {
        qInfo("No Session in Progress");
    }
}

void NeuresetDevice::pauseTimerOver(){
    // after 5 mins contact is not restablished
    cancelSession();

    // turn device off.
    emit pauseTimerElapsed();

    qInfo("Pause timer elapsed");

}


void NeuresetDevice::handlePercentage() {
    currEvents++;
    percentage = (currEvents * 100) / totalEvents;
    emit sessionProgress(percentage);
}

