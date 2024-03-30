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
    Counter* sessionTimer;
    SessionLog* sessionLog;
    QList<QFuture<QPair<Electrode*, double>>> baselineFutures;
    QFutureWatcher<QPair<Electrode*, double>>* watcher;
    void calculateOverallBaseline();



public:
    NeuresetDevice(EEGHeadset* headset, QObject* parent = nullptr);
    void startSession();  
    SessionLog* getSessionLog() const { return sessionLog; }

public slots:
    void pauseSession();
    void resumeSession();
    void endSession();
    void gotNewSession(Session* session);

signals:
    void sessionStarted();
    void sessionPaused();
    void sessionResumed();
    void sessionEnded();
private slots:
    void onBaselineCalculationFinished();
};


#endif // NEURESETDEVICE_H
