#include "electrode.h"

Electrode::Electrode(int id, QObject* parent) : QObject(parent), id(id), baselineFrequency(0.0), offsetFrequency(5.0), treatmentDuration(1.0), timeElapsed(0.0) {
    treatmentTimer = new QTimer(this);
    connect(treatmentTimer, &QTimer::timeout, this, &Electrode::onTreatmentTimerTimeout);
    session = new Session(parent);
}

// Setter methods
void Electrode::setBaselineFrequency(double baseline) { baselineFrequency = baseline; }
void Electrode::setOffsetFrequency(double offset) { offsetFrequency = offset; }
void Electrode::setTreatmentDuration(double duration) { treatmentDuration = duration; }

// Getter methods
int Electrode::getId() const { return id; }
double Electrode::getBaselineFrequency() const { return baselineFrequency; }
double Electrode::getOffsetFrequency() const { return offsetFrequency; }
double Electrode::getTreatmentDuration() const { return treatmentDuration; }

// Calculate baseline frequency
double Electrode::calculateBaseline() {
    // Human brain frequencies range from 0.5 to 100 Hz, so let's pick a random value in that range for the baseline
    baselineFrequency = rand() % 100;
    QMap<int, double> before;
    before.insert(id, baselineFrequency);
    session->setBeforeBaseline(before);
    return  baselineFrequency;
}

// Calculate offset frequency
double Electrode::calculateOffsetFrequency() {
    // 5 Hz added to baseline
    offsetFrequency += 5.0;
    return offsetFrequency;
}

// Apply treatment
void Electrode::applyTreatment() {
    timeElapsed = 0.0;
    treatmentTimer->start(62); // Start the timer with a 1/16th of a second interval (approximately)
}

// Handle adding offset
void Electrode::onTreatmentTimerTimeout() {
    baselineFrequency += offsetFrequency;
    timeElapsed += 0.062; // Increment by 1/16th of a second (0.062 seconds)

    if (timeElapsed >= treatmentDuration) {
        treatmentTimer->stop();
        QMap<int, double> after;
        after.insert(id, baselineFrequency);
        session->setAfterBaseline(after);
        emit treatmentApplied(session);
        qInfo("Treatment applied for electrode %d", id);
    }
}



