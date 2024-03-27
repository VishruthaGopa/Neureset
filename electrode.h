#ifndef ELECTRODE_H
#define ELECTRODE_H

#include <QObject>
#include <QTimer>
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
    Session *session;

public:
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

private slots:
    void onTreatmentTimerTimeout();

signals:
    void treatmentApplied(Session *session);

};

#endif // ELECTRODE_H



