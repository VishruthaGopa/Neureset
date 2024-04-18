#ifndef ELECTRODE_H
#define ELECTRODE_H
#include <QObject>
#include <QTimer>
#include<QRandomGenerator>
#include <QEventLoop>
#include "session.h"
#include <complex>
#include <vector>
#include <cmath>
#include <algorithm>
#include <QDebug>
#include <QCoreApplication>
#include <QtMath>
#include <QVector>
#include <QtCharts>


class Electrode : public QObject {
    Q_OBJECT
private:
    int id;
    double baselineFrequency;
    double offsetFrequency;
    double treatmentDuration;
    double timeElapsed;
    double samplingFrequency; // Sampling frequency
    double duration; // Duration of the waveform
    std::vector<double> waveform;
    QtCharts::QChartView *chartView;
    QtCharts::QChart *chart;
    QtCharts::QLineSeries *series;
    std::vector<double> Beforewaveform;
    std::vector<double> Afterwaveform;

public:
    const double PI = 3.14159265358979323846;
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


    void generateAlphaWave();
    void generateDeltaWave();
    void generateBetaWave();
    void generateThetaWave();
    void generateGammaWave();

    void generateBrainWaveFrequency();
    double calculateDominantFrequency();
    QtCharts::QChartView* plotWaveform(bool);
    void generateFromBaseline();
signals:
    void treatmentApplied(double fre);
    void baselineMeasured(double fre);

};

#endif // ELECTRODE_H
