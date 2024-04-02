#ifndef NEURESETDEVICE_H
#define NEURESETDEVICE_H

#include<QObject>
#include<QTimer>
#include "sessionlog.h"
#include "eegheadset.h"
#include "counter.h"
#include "sessionlog.h"
#include "session.h"
#include "electrode.h"
#include<QFutureWatcher>
#include<QFuture>
#include<QPair>
#include<QtConcurrent/QtConcurrent>



class NeuresetDevice : public QObject {
    Q_OBJECT
private:
    EEGHeadset* eegHeadset;
    bool sessionInProgress;
    bool sessionPaused;
    QTimer* sessionTimer;
    SessionLog* sessionLog;
    int stage1;
    int stage2;
    int stage3;
    int stage4;
    QList<QFuture<QPair<Electrode*, double>>> baselineFutures;
    QFutureWatcher<QPair<Electrode*, double>>* watcher;
    void calculateOverallBaseline();
    void stopTreatment();



public:
    NeuresetDevice(EEGHeadset* headset, QObject* parent = nullptr);
    void startSession();  
    SessionLog* getSessionLog() const { return sessionLog; }
    void gotNewSession(Session* session);
    void endSession();
    void pauseSession();
    void resumeSession();
    void treatNextHandler();


};


#endif // NEURESETDEVICE_H
