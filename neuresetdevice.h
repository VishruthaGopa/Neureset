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
    QTimer* pauseTimer;
    QTimer* percentageTimer;
    SessionLog* sessionLog;
    int stage;
    QList<QFuture<QPair<Electrode*, double>>> baselineFutures;
    QFutureWatcher<QPair<Electrode*, double>>* watcher;
    int percentage;
    int totalEvents;
    int currEvents;
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
    void cancelSession();
    EEGHeadset* getHeadset();
    void handlePercentage();
    void onTreatmentCompleted(double frequency);
    void measurementHandler();
    void treatNextHandler(double frequency);
    QVector<Electrode*> getElectrodes(){return eegHeadset->getElectrodes();}

signals:
     void sessionProgress(int percentage);
     void treatmentAppliedSignal(); //green light signal

};


#endif // NEURESETDEVICE_H
