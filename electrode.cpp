#include "electrode.h"

Electrode::Electrode(int id, QObject* parent) : QObject(parent), id(id), baselineFrequency(0.0), offsetFrequency(5.0), treatmentDuration(1.0), timeElapsed(0.0) {
    treatmentTimer = new QTimer(this);
    connect(treatmentTimer, &QTimer::timeout, this, &Electrode::onTreatmentTimerTimeout);
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
    baselineFrequency = generateBrainFrequency();
    emit baselineMeasured(baselineFrequency);
    return  baselineFrequency;
}

// Calculate offset frequency
double Electrode::calculateOffsetFrequency() {
    return offsetFrequency;
}

// Apply treatment
void Electrode::applyTreatment() {
    timeElapsed = 0.0;
    treatmentTimer->start(62); // Start the timer with a 1/16th of a second interval (approximately)
}

// Handle adding offset
void Electrode::onTreatmentTimerTimeout() {
    baselineFrequency = abs(baselineFrequency-offsetFrequency);
    //When you add two phrequencies you observe beat phenomina, which results in the
    //new dominent frequency is the difference of the two
    timeElapsed += 0.062; // Increment by 1/16th of a second (0.062 seconds)

    if (timeElapsed >= treatmentDuration) {
        treatmentTimer->stop();
        qInfo("Treatment applied for electrode %d at %d", id,static_cast<int>(offsetFrequency));
        emit treatmentApplied(baselineFrequency);
    }
}

// Function to generate a random brainwave frequency
double Electrode::generateBrainFrequency() {
    // Generate a random brainwave type
    BrainWaveType waveType = static_cast<BrainWaveType>(QRandomGenerator::global()->bounded(TotalBrainWaveTypes));

    // Generate frequency based on the randomly selected brainwave type
    double frequency = 0.0;

    // Generate frequency based on the selected brainwave type
    switch (waveType) {
        case Delta:
            frequency = QRandomGenerator::global()->generateDouble() * (4.0 - 0.5) + 0.5;// Delta waves (0.5 - 4 Hz)
            break;
        case Theta:
            frequency = QRandomGenerator::global()->generateDouble() * (8.0 - 4.0) + 4.0; // Theta waves (4 - 8 Hz)
            break;
        case Alpha:
            frequency =QRandomGenerator::global()->generateDouble() * (14.0 - 8.0) + 8.0; // Alpha waves (8 - 14 Hz)
            break;
        case Beta:
            frequency = QRandomGenerator::global()->generateDouble() * (30.0 - 14.0) + 14.0;  // Beta waves (14 - 30 Hz)
            break;
        case Gamma:
            frequency = QRandomGenerator::global()->generateDouble() * (100.0 - 30.0) + 30.0; // Gamma waves (30 - 100 Hz)
            break;
        default:
            break;
    }

    return frequency;
}


