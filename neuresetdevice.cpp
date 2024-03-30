#include "neuresetdevice.h"

NeuresetDevice::NeuresetDevice(EEGHeadset* headset, QObject* parent) : QObject(parent), sessionInProgress(false) {
 sessionTimer = new Counter();
 sessionLog = new SessionLog();
 eegHeadset=headset;
 watcher = new QFutureWatcher<QPair<Electrode*, double>>(this);
 QObject::connect(eegHeadset,&EEGHeadset::newSession,this,&NeuresetDevice::gotNewSession);
 QObject::connect(watcher, &QFutureWatcher<QPair<Electrode*, double>>::finished, this, &NeuresetDevice::onBaselineCalculationFinished);
 QObject::connect(sessionTimer, &Counter::sessionStarted, this, &NeuresetDevice::startSession);
 QObject::connect(sessionTimer, &Counter::sessionPaused, this, &NeuresetDevice::pauseSession);
 QObject::connect(sessionTimer, &Counter::sessionResumed, this, &NeuresetDevice::resumeSession);
 QObject::connect(sessionTimer, &Counter::sessionEnded, this, &NeuresetDevice::endSession);

}

void NeuresetDevice::calculateOverallBaseline() {
    // Clear previous baseline futures
    for (const auto& future : baselineFutures) {
        disconnect(watcher, &QFutureWatcher<QPair<Electrode*, double>>::finished, this, &NeuresetDevice::onBaselineCalculationFinished);
    }
    baselineFutures.clear();

    // Iterate through all EEG sites and calculate baseline concurrently
    for (int i = 0; i < 21; ++i) {
        Electrode* electrode = eegHeadset->getElectrodeSite(i);
        QFuture<QPair<Electrode*, double>> future = QtConcurrent::run([electrode]() {
            double baseline = electrode->calculateBaseline();
            return qMakePair(electrode, baseline);
        });
        baselineFutures.append(future);
    }

    // Set up the watcher to monitor the futures
    for (const auto& future : baselineFutures) {
        watcher->setFuture(future);
    }
}




void NeuresetDevice::onBaselineCalculationFinished() {
    QFuture<QPair<Electrode*, double>> future = watcher->future();
    QPair<Electrode*, double> result = future.result();

    Electrode* electrode = result.first;
    double baseline = result.second;

    // Handle baseline result, you can store it or utilize it as needed

    // Example: Store the baseline in a QMap
    QMap<Electrode*, double> overallBaseline;
    overallBaseline.insert(electrode, baseline);

}

void NeuresetDevice::gotNewSession(Session* session){
    sessionLog->addSession(session);
}

void NeuresetDevice::startSession(){
    if(!sessionInProgress){
        sessionInProgress=true;
        //handle start
    }
    else{
        qInfo("Session already in Progress");
    }
}

void NeuresetDevice::endSession(){
    if(sessionInProgress){
        sessionInProgress=false;
        //handle start
    }
    else{
        qInfo("No Session in Progress");
    }
}

void NeuresetDevice::pauseSession(){
    if(sessionInProgress){
       //handle pause
    }
    else{
        qInfo("No session in progress");
    }
}

void NeuresetDevice::resumeSession(){
    if(sessionInProgress){
       //handle pause
    }
    else{
        qInfo("No Session in Progress");
    }
}
