#include "eegheadset.h"

EEGHeadset::EEGHeadset(QObject* parent) : QObject(parent) {
    // Create and initialize electrodes
       session=new Session();
       for (int i = 1; i < 22; ++i) {
           Electrode* electrode=new Electrode(i);
           electrodeSites.append(electrode);
           QObject::connect(electrode,&Electrode::treatmentApplied,this,&EEGHeadset::handleTreatmentApplied);
           QObject::connect(electrode,&Electrode::baselineMeasured,this,&EEGHeadset::handleBaseline);
       }
       //set the for the first electrode
       currElectrode=1;
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



bool EEGHeadset::treatNext(){
   if (currElectrode==1){
       session->startTimer();
   }
   electrodeSites[currElectrode-1]->applyTreatment();
   if(currElectrode==21){
       return false;
   }
   else{
       currElectrode+=1;
       return true;
   }
}


void EEGHeadset::startMeasurement() {
  session->startTimer();
  // Start baseline measurement for each electrode
  for (int i = 0; i < electrodeSites.size(); ++i) {
      QThread *thread = new QThread;
      electrodeSites[i]->moveToThread(thread);
      connect(thread, &QThread::started, electrodeSites[i], &Electrode::calculateBaseline);
      connect(electrodeSites[i], &Electrode::baselineMeasured, thread, &QThread::quit);
      connect(thread, &QThread::finished, thread, &QThread::deleteLater);
      connect(thread, &QThread::finished, electrodeSites[i], &QObject::deleteLater);
      thread->start();
  }
}

void EEGHeadset::handleBaseline(double frequency) {
  baselineFrequencies.append(frequency);
  if (baselineFrequencies.size() == 21) {
      // All baselines measured, calculate average
      qDebug()<<baselineFrequencies;
      double average = calculateDominantFrequency(baselineFrequencies);
      session->setBeforeBaseline(average);
      qDebug() << "Average baseline frequency:" << average;
  }
}



void EEGHeadset::handleTreatmentApplied(double frequency){
   afterFrequencies.append(frequency);
   if (afterFrequencies.size() == 21) {
       session->endTimer();
       // All baselines measured, calculate average
       double sum = 0;
       foreach (double freq, afterFrequencies) {
           sum += freq;
       }
       double average = sum / afterFrequencies.size();
       session->setAfterBaseline(average);
       qDebug() << "Average after frequency:" << average;
       emit newSession(session);
   }
}

void EEGHeadset::createNewSession(){
   session=new Session();
}

/*
This function takes a vector of frequencies as input and returns the dominant frequency.
It creates a signal vector by converting each frequency to a complex number.
Then it performs FFT on the signal vector. It finds the index of the maximum magnitude in the FFT result (excluding the DC component at index 0).
Finally, it calculates the dominant frequency using the index of the maximum magnitude and the sample rate.

*/
double EEGHeadset::calculateDominantFrequency(const QVector<double> &frequencies) {
    int N = frequencies.size();
    QVector<Complex> signal(N);

    // Populate the signal vector with complex numbers
    for (int i = 0; i < N; ++i) {
        signal[i] = Complex(frequencies[i], 0.0);
    }

    // Perform FFT
    QVector<Complex> fftResult = fft(signal);

    // Find the index of the maximum magnitude in the FFT result
    int maxIndex = 0;
    double maxMagnitude = 0.0;
    for (int i = 1; i < N / 2; ++i) { // Start from index 1 to skip the DC component at index 0
        double magnitude = sqrt(pow(fftResult[i].real, 2) + pow(fftResult[i].imag, 2));
        if (magnitude > maxMagnitude) {
            maxMagnitude = magnitude;
            maxIndex = i;
        }
    }

    // Calculate dominant frequency
    double sampleRate = 200; // Sample rate in Hz (as recommmended sample rate is  double max Frequency)
    double dominantFrequency = maxIndex * sampleRate / N;

    return dominantFrequency;
}

