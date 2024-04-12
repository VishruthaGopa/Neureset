// eegheadset.cpp
#include "eegheadset.h"

EEGHeadset::EEGHeadset(QObject* parent) : QObject(parent) {
   // Create and initialize electrodes
   session = new Session();
   paused = false;
   for (int i = 1; i < 22; ++i) {
       Electrode* electrode = new Electrode(i);
       electrodeSites.append(electrode);
   }

   for (Electrode *electrode : electrodeSites) {
       QObject::connect(electrode, &Electrode::treatmentApplied, this, &EEGHeadset::handleTreatmentApplied);
       QObject::connect(electrode, &Electrode::baselineMeasured, this, &EEGHeadset::handleBaseline);
   }

   // Set the first electrode
   currElectrodeTreatment = 1;
   currElectrodeMeasurement = 1;
   measurementInProgress=false;
   treatmentInProgress=false;
   currStage=0;
   calculationTimer = new QTimer();
   QObject::connect(calculationTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
}

EEGHeadset::~EEGHeadset() {
   qDeleteAll(electrodeSites);
   electrodeSites.clear();
   if (session != nullptr) {
       delete session;
   }
}

Electrode* EEGHeadset::getElectrodeSite(int index) const {
   if (index >= 0 && index < electrodeSites.size()) {
       return electrodeSites[index];
   }
   return nullptr;
}

void EEGHeadset::startTreatment(double frequency) {
   currStage = frequency;
   treatmentInProgress=true;
   if (!paused) {
       QFutureSynchronizer<void> synchronizer;
       for (int i = currElectrodeTreatment - 1; i < electrodeSites.size(); ++i) {
           synchronizer.addFuture(QtConcurrent::run([=] {
               electrodeSites[i]->setOffsetFrequency(frequency);
               electrodeSites[i]->applyTreatment();
           }));
       }
       synchronizer.waitForFinished();
       currElectrodeTreatment=1;
   }
}

void EEGHeadset::startMeasurement() {
   measurementInProgress = true;
   wait(5);
   if (!paused) {
       QFutureSynchronizer<void> synchronizer;
       for (int i = currElectrodeMeasurement - 1; i < electrodeSites.size(); ++i) {
           synchronizer.addFuture(QtConcurrent::run([=] {
               electrodeSites[i]->calculateBaseline();
           }));
       }
       synchronizer.waitForFinished();
   }
}

void EEGHeadset::wait(int sec) {
   QEventLoop loop;
   QTimer::singleShot(1000*sec, &loop, &QEventLoop::quit); // Wait for seconds
   loop.exec();
}

void EEGHeadset::handleBaseline(double frequency) {
   if (!paused) {
       baselineFrequencies.append(frequency);
       if(baselineFrequencies.size() == 105){
           // All baselines measured, calculate dominant
           double average = calculateDominantFrequency(baselineFrequencies);
           session->setAfterBaseline(average);
           qDebug() << "Average after frequency:" << average;
           //send out session details
           emit newSession(session);
           createNewSession();
           //cleanup data from electrodes
           afterFrequencies.clear();
           baselineFrequencies.clear();
           currElectrodeTreatment= 1;
           currElectrodeMeasurement = 1;
           measurementInProgress = false;
           currStage=0;
           //reset electrodes
           for(Electrode * electrode: electrodeSites){
               electrode->setBaselineFrequency(0);
           }
           emit measurementCompleted();
       }
       else if (baselineFrequencies.size()==21){
           // All baselines measured, calculate dominant
           double average = calculateDominantFrequency(baselineFrequencies);
           session->setBeforeBaseline(average);
           currElectrodeMeasurement = 1;
           measurementInProgress = false;
           qDebug() << "Average baseline frequency:" << average;
           
           // Emit signal indicating measurement completion
           emit measurementCompleted();
       }
       else if (baselineFrequencies.size() % 21==0) {
           // All baselines measured, calculate dominant
           double average = calculateDominantFrequency(baselineFrequencies);
           currElectrodeMeasurement = 1;
           measurementInProgress = false;
           qDebug() << "Average baseline frequency:" << average;
           // Emit signal indicating measurement completion
           emit measurementCompleted();
       }
   }
}

void EEGHeadset::handleTreatmentApplied(double frequency) {
   if (!paused) {
       afterFrequencies.append(frequency);
       if(afterFrequencies.size()%21==0){
           wait(1);
           emit treatmentCompleted(currStage);
           currElectrodeTreatment= 1;
           treatmentInProgress=false;
       }
   }
}

void EEGHeadset::createNewSession() {
   session = new Session();
}

double EEGHeadset::calculateDominantFrequency(const QVector<double> &frequencies) {
    int N = frequencies.size();
    int windowSize = 21; // Consider the last 21 values

    // Check if the size of frequencies is less than the desired window size
    if (N < windowSize) {
        // Handle the case when there are fewer than 21 values
        return 0.0; // or some appropriate default value
    }

    QVector<std::complex<double>> X(windowSize);

    // Compute DFT using only the last 21 values
    for (int k = 0; k < windowSize; ++k) {
        std::complex<double> sum = 0;
        for (int n = N - windowSize; n < N; ++n) { // Consider the last 21 values
            sum += frequencies[n] * std::exp(std::complex<double>(0, -2 * M_PI * k * n / N));
        }
        X[k] = sum;
    }

    // Compute magnitude spectrum
    QVector<double> magnitudes(windowSize);
    for (int k = 0; k < windowSize; ++k) {
        magnitudes[k] = std::abs(X[k]);
    }

    // Find index of max magnitude
    double maxMagnitude = magnitudes[0];
    int maxIndex = 0;
    for (int k = 1; k < windowSize; ++k) {
        if (magnitudes[k] > maxMagnitude) {
            maxMagnitude = magnitudes[k];
            maxIndex = k;
        }
    }

    // Return the corresponding frequency from the original list
    return frequencies[N - windowSize + maxIndex];
}



void EEGHeadset::cancelSession() {
   delete session;
   createNewSession();
   afterFrequencies.clear();
   baselineFrequencies.clear();
   currElectrodeMeasurement = 1;
   currElectrodeTreatment=1;
   treatmentInProgress=false;
   measurementInProgress=false;
   currStage = 0;
   qInfo("Connection Lost Session Canceled.");
   paused = false;
}

void EEGHeadset::pauseSession() {
   paused = true;
}

void EEGHeadset::resumeSession() {
   paused = false;
   if (measurementInProgress==true){
       startMeasurement();
   }
   if (treatmentInProgress==true){
       startTreatment(currStage);
   }
}

void EEGHeadset::startSession(){
    session->startTimer();
}
