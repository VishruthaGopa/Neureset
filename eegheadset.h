#ifndef EEGHEADSET_H
#define EEGHEADSET_H
#include<QObject>
#include<QTimer>
#include <QThread>
#include<QFutureWatcher>
#include<QFuture>
#include<QPair>
#include<complex>
#include<QtConcurrent/QtConcurrent>
#include "session.h"
#include "electrode.h"


class EEGHeadset : public QObject {
    Q_OBJECT
private:
    QVector<Electrode*> electrodeSites;
    QVector<double> baselineFrequencies;
    QVector<double> afterFrequencies;
    Session* session;
    int currElectrodeTreatment ;
    int currElectrodeMeasurement;
    bool measurementInProgress;
    bool treatmentInProgress;
    int currStage;
    QTimer* calculationTimer;
    QEventLoop loop;
    bool paused;


public:
    EEGHeadset(QObject* parent = nullptr);

    // Destructor to free memory allocated for electrodes
    ~EEGHeadset();

    // Function to get an electrode site by index
    Electrode* getElectrodeSite(int index) const;
    void createNewSession();
    bool treatNext(double );
    void startMeasurement();
    void handleBaseline(double frequency);
    void handleTreatmentApplied(double frequency);
    //handle required timing
    void wait(int seconds);
    void pauseSession();
    void startTreatment(double frequency);
    void resumeSession();
    void startSession();

    // Function to calculate FFT and return dominant frequency
    double calculateDominantFrequency(const QVector<double> &frequencies);
    void cancelSession();


signals:
    void newSession(Session *session);
    void treatmentCompleted(double feq);
    void measurementCompleted();
    //void treatmentAppliedSignal(); //green light signal
};



#endif // EEGHEADSET_H
