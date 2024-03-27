#include "eegheadset.h"

EEGHeadset::EEGHeadset(QObject* parent) : QObject(parent) {
    // Create and initialize electrodes
    for (int i = 0; i < 21; ++i) {
        Electrode* electrode=new Electrode(i);
        electrodeSites.append(electrode);
        QObject::connect(electrode,&Electrode::treatmentApplied,this,&EEGHeadset::handleTreatmentApplied);

    }
}

// Destructor to free memory allocated for electrodes
EEGHeadset::~EEGHeadset() {
    qDeleteAll(electrodeSites);
    electrodeSites.clear();
}

// Function to get an electrode site by index
Electrode* EEGHeadset::getElectrodeSite(int index) const {
    if (index >= 0 && index < electrodeSites.size()) {
        return electrodeSites[index];
    }
    return nullptr;
}

void EEGHeadset::handleTreatmentApplied(Session* session){
    emit newSession(session);
}
