#include "neuresetdevice.h"

NeuresetDevice::NeuresetDevice(EEGHeadset* headset, QObject* parent) : QObject(parent), sessionInProgress(false)
,stage1(0),stage2(0),stage3(0),stage4(0){
 sessionTimer = new QTimer(this);
 QObject::connect(sessionTimer, &QTimer::timeout, this, &NeuresetDevice::treatNextHandler);
 sessionLog = new SessionLog();
 eegHeadset=headset;
 watcher = new QFutureWatcher<QPair<Electrode*, double>>(this);
 percentage=0;
 totalEvents=84;
 currEvents=0;
 QObject::connect(eegHeadset,&EEGHeadset::newSession,this,&NeuresetDevice::gotNewSession);
}

void NeuresetDevice::calculateOverallBaseline() {
    eegHeadset->startMeasurement();
}

void NeuresetDevice::stopTreatment() {
    sessionTimer->stop();
    sessionInProgress = false;
}

void NeuresetDevice::gotNewSession(Session* session){
    sessionLog->addSession(session);
}

void NeuresetDevice::startSession() {
   if (!sessionInProgress) {
       sessionInProgress = true;
       //handle start
       calculateOverallBaseline();
       sessionTimer->start(1000);
   } else {
       qInfo("Session already in Progress");
   }
}

void NeuresetDevice::treatNextHandler() {
    if (sessionInProgress) {
        if (stage1 < 21) {
            eegHeadset->treatNext(5.0);
            stage1++;
            currEvents++;
        }
        else if (stage2 < 21) {
            eegHeadset->treatNext(10.0);
            stage2++;
            currEvents++;
        }
        else if (stage3 < 21) {
            eegHeadset->treatNext(15.0);
            stage3++;
            currEvents++;
        }
        else if (stage4 < 21) {
            eegHeadset->treatNext(20.0);
            stage4++;
            currEvents++;
        }
        else {
            // All treatments completed, end the session
            endSession();
            return;
        }
         percentage=(currEvents*100)/totalEvents;
         sessionProgress(percentage);
    }
}

void NeuresetDevice::endSession(){
    if(sessionInProgress){
        sessionInProgress=false;
        stage1=0;
        stage2=0;
        stage3=0;
        stage4=0;
        percentage=0;
        currEvents=0;
        stopTreatment();
    }
    else{
        qInfo("No Session in Progress");
    }
}

void NeuresetDevice::pauseSession(){
    if(sessionInProgress){
       stopTreatment();
    }
    else{
        qInfo("No session in progress");
    }
}

void NeuresetDevice::resumeSession(){
    if(sessionInProgress){
       sessionTimer->start(1000);
       sessionInProgress = false;
    }
    else{
        qInfo("No Session in Progress");
    }
}
