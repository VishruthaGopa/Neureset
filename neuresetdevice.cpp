#include "neuresetdevice.h"

NeuresetDevice::NeuresetDevice(EEGHeadset* headset, QObject* parent) : QObject(parent), sessionInProgress(false) {
 sessionTimer = new Counter();
 sessionLog = new SessionLog();
 eegHeadset=headset;
 watcher = new QFutureWatcher<QPair<Electrode*, double>>(this);
 QObject::connect(eegHeadset,&EEGHeadset::newSession,this,&NeuresetDevice::gotNewSession);
 QObject::connect(sessionTimer, &Counter::sessionStarted, this, &NeuresetDevice::startSession);
 QObject::connect(sessionTimer, &Counter::sessionPaused, this, &NeuresetDevice::pauseSession);
 QObject::connect(sessionTimer, &Counter::sessionResumed, this, &NeuresetDevice::resumeSession);
 QObject::connect(sessionTimer, &Counter::sessionEnded, this, &NeuresetDevice::endSession);

}

void NeuresetDevice::calculateOverallBaseline() {
    eegHeadset->startMeasurement();
}


void NeuresetDevice::gotNewSession(Session* session){
    sessionLog->addSession(session);
}

void NeuresetDevice::startSession(){
    if(!sessionInProgress){
        sessionInProgress=true;
        //handle start
        calculateOverallBaseline();
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
