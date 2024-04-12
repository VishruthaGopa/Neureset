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
   treatmentInProgress=-1;
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
   treatmentInProgress = frequency;
   if (!paused) {
       QFutureSynchronizer<void> synchronizer;
       for (int i = currElectrodeTreatment - 1; i < electrodeSites.size(); ++i) {
           synchronizer.addFuture(QtConcurrent::run([=] {
               electrodeSites[i]->setOffsetFrequency(frequency);
               electrodeSites[i]->applyTreatment();
           }));
       }
       synchronizer.waitForFinished();
       treatmentInProgress = -1;
       currElectrodeTreatment=1;
   }
}

void EEGHeadset::startMeasurement() {
   measurementInProgress = true;
   wait(5);
   session->startTimer();
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
   QTimer::singleShot(1000+sec, &loop, &QEventLoop::quit); // Wait for seconds
   loop.exec();
}

void EEGHeadset::handleBaseline(double frequency) {
   if (!paused) {
       baselineFrequencies.append(frequency);
       if (baselineFrequencies.size() == 21) {
           // All baselines measured, calculate dominant
           double average = calculateDominantFrequency(baselineFrequencies);
           session->setBeforeBaseline(average);
           currElectrodeMeasurement = 1;
           measurementInProgress = false;
           qDebug() << "Average baseline frequency:" << average;
           baselineFrequencies.clear();
           // Emit signal indicating measurement completion
           emit measurementCompleted();

       }
   }
}

void EEGHeadset::handleTreatmentApplied(double frequency) {
   if (!paused) {
       wait(1);
       afterFrequencies.append(frequency);
       if (afterFrequencies.size() == 84) {
           double average = calculateDominantFrequency(afterFrequencies);
           session->setAfterBaseline(average);

           qDebug() << "Average after frequency:" << average;
           emit newSession(session);
           createNewSession();
           afterFrequencies.clear();
           baselineFrequencies.clear();
           currElectrodeTreatment= 1;

            // Flashing green signal here
            emit treatmentAppliedSignal();
       }
       else if(afterFrequencies.size()%21==0){
           emit treatmentCompleted(treatmentInProgress);
           currElectrodeTreatment= 1;
       }
   }
}

void EEGHeadset::createNewSession() {
   session = new Session();
}

double EEGHeadset::calculateDominantFrequency(const QVector<double> &frequencies) {
   int N = frequencies.size();
   QVector<std::complex<double>> X(N);

   // Compute DFT
   for (int k = 0; k < N; ++k) {
       std::complex<double> sum = 0;
       for (int n = 0; n < N; ++n) {
           sum += frequencies[n] * std::exp(std::complex<double>(0, -2 * M_PI * k * n / N));
       }
       X[k] = sum;
   }

   // Compute magnitude spectrum
   QVector<double> magnitudes(N);
   for (int k = 0; k < N; ++k) {
       magnitudes[k] = std::abs(X[k]);
   }

   // Find index of max magnitude
   double maxMagnitude = magnitudes[0];
   int maxIndex = 0;
   for (int k = 1; k < N; ++k) {
       if (magnitudes[k] > maxMagnitude) {
           maxMagnitude = magnitudes[k];
           maxIndex = k;
       }
   }

   return frequencies[maxIndex];
}

void EEGHeadset::cancelSession() {
   delete session;
   createNewSession();
   afterFrequencies.clear();
   baselineFrequencies.clear();
   currElectrodeMeasurement = 1;
   currElectrodeTreatment=1;
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
   if (treatmentInProgress!=-1){
       startTreatment(treatmentInProgress);
   }
}

