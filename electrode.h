#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <QObject>
#include <QTimer>
#include<QRandomGenerator>
#include <QDebug>
#include "session.h"

class Electrode : public QObject {
    Q_OBJECT
private:
    int id;
    double baselineFrequency;
    double offsetFrequency;
    double treatmentDuration;
    double timeElapsed;
    QTimer* treatmentTimer;

public:
    enum BrainWaveType {
           Delta,
           Theta,
           Alpha,
           Beta,
           Gamma,
           TotalBrainWaveTypes //track the total number of brainwave types
     };

    Electrode(int id, QObject* parent = nullptr);

    // Setter methods
    void setBaselineFrequency(double baseline);
    void setOffsetFrequency(double offset);
    void setTreatmentDuration(double duration);

    // Getter methods
    int getId() const;
    double getBaselineFrequency() const;
    double getOffsetFrequency() const;
    double getTreatmentDuration() const;

    // Calculate baseline frequency
    double calculateBaseline();

    // Calculate offset frequency
    double calculateOffsetFrequency();

    // Apply treatment
    void applyTreatment();


    // Function to generate a random brainwave frequency
    static double generateBrainFrequency() ;

private slots:
    void onTreatmentTimerTimeout();

signals:
    void treatmentApplied(double fre);
    void baselineMeasured(double fre);

};

#endif // ELECTRODE_H



