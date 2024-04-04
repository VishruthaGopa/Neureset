#include "eegheadset.h"

EEGHeadset::EEGHeadset(QObject* parent) : QObject(parent) {
    // Create and initialize electrodes
       session=new Session();
       for (int i = 1; i < 22; ++i) {
           Electrode* electrode=new Electrode(i);
           electrodeSites.append(electrode);
       }


       for (Electrode *electrode : electrodeSites) {
           QObject::connect(electrode, &Electrode::treatmentApplied, this, &EEGHeadset::handleTreatmentApplied);
           QObject::connect(electrode,&Electrode::baselineMeasured,this,&EEGHeadset::handleBaseline);
       }

       //set the for the first electrode
       currElectrode=1;
       calculationTimer=new QTimer();
       QObject::connect(calculationTimer,&QTimer::timeout,&loop,&QEventLoop::quit);
}


// Destructor to free memory allocated for electrodes
EEGHeadset::~EEGHeadset() {
   qDeleteAll(electrodeSites);
   electrodeSites.clear();
   if(session!=nullptr){
       delete session;
   }
}

// Function to get an electrode site by index
Electrode* EEGHeadset::getElectrodeSite(int index) const {
   if (index >= 0 && index < electrodeSites.size()) {
       return electrodeSites[index];
   }
   return nullptr;
}



bool EEGHeadset::treatNext(double frequency){
   electrodeSites[currElectrode-1]->setOffsetFrequency(frequency);
   electrodeSites[currElectrode-1]->applyTreatment();
   if(currElectrode==21){
       currElectrode=1;
       return false;
   }
   else{
       currElectrode+=1;
       return true;
   }
}


void EEGHeadset::startMeasurement() {
  session->startTimer();
  // Use a QFutureWatcher to monitor the completion of the futures
  QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
  connect(watcher, &QFutureWatcher<void>::finished, [=]() {
      watcher->deleteLater(); // Clean up QFutureWatcher
  });

  // Concurrently call processObject on each object
  QFuture<void> future = QtConcurrent::map(electrodeSites, [this](Electrode *obj) {
      obj->calculateBaseline();
  });

  // Set the future for the watcher
  watcher->setFuture(future);

}

void EEGHeadset::handleBaseline(double frequency) {
  baselineFrequencies.append(frequency);

  if (baselineFrequencies.size() == 21) {
      // All baselines measured, calculate dominent
      double average = calculateDominantFrequency(baselineFrequencies);
      session->setBeforeBaseline(average);
      qDebug() << "Average baseline frequency:" << average;
  }
}



void EEGHeadset::handleTreatmentApplied(double frequency){
   afterFrequencies.append(frequency);
   //qDebug()<<afterFrequencies.size();
   if (afterFrequencies.size() == 84) {
       double average = calculateDominantFrequency(afterFrequencies);
       session->setAfterBaseline(average);
       qDebug() << "Average after frequency:" << average;
       session->endTimer();
       emit newSession(session);
       createNewSession();
       afterFrequencies.clear();
       baselineFrequencies.clear();
       currElectrode=1;

   }
}

void EEGHeadset::createNewSession(){
   session=new Session();
}

/*
The function calculateDominantFrequency calculates the Discrete Fourier Transform (DFT) of a time-domain signal represented by a QVector<double>.
It iterates over each frequency component, computing the DFT coefficient using the DFT formula.
Then, it computes the magnitude spectrum by taking the absolute value of each DFT coefficient.
Finally, it identifies the dominant frequency by finding the index with the maximum magnitude
in the magnitude spectrum and returns the corresponding frequency from the original list.
This function provides a way to analyze the frequency content of a signal and determine its dominant frequency component.

*/
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




