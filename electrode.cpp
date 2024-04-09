#include "electrode.h"

Electrode::Electrode(int id, QObject* parent) : QObject(parent), id(id), offsetFrequency(5.0), treatmentDuration(1.0), timeElapsed(0.0),samplingFrequency(1000),duration(1.0) {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned>(time(nullptr)));
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
    qInfo("Generating WaveForm for Electrode, %d",id);
    generateBrainWaveFrequency();
    baselineFrequency=calculateDominantFrequency();
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
    baselineFrequency+=offsetFrequency;
    qInfo("Treatment applied for electrode %d at %d", id,static_cast<int>(offsetFrequency));
    emit treatmentApplied(baselineFrequency);
}


// Function to generate a random brainwave
void Electrode::generateBrainWaveFrequency() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 4); // For selecting one of the five types

    int waveType = distribution(generator); // 0: alpha, 1: beta, 2: delta, 3: theta, 4: gamma

    switch(waveType) {
        case 0: // Alpha wave
            generateAlphaWave();
            break;
        case 1: // Beta wave
            generateBetaWave();
            break;
        case 2: // Delta wave
            generateDeltaWave();
            break;
        case 3: // Theta wave
            generateThetaWave();
            break;
        case 4: // Gamma wave
            generateGammaWave();
            break;
        default:
            generateAlphaWave(); // Default to alpha wave
            break;
    }

}


void Electrode::generateAlphaWave() {
    // Varying the frequencies slightly
    double freq1 = 10.0 + (rand() % 3 - 1); // Random value between 9 and 11
    double freq2 = 20.0 + (rand() % 3 - 1); // Random value between 19 and 21
    int numSamples = static_cast<int>(duration * samplingFrequency);
    waveform.resize(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        double t = i / samplingFrequency;
        waveform[i] = sin(freq1 * 2 * M_PI * t) + 0.5 * sin(freq2 * 2 * M_PI * t);
    }
    // Adding random noise to the alpha wave
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 0.1);
    double noise = distribution(generator);
    waveform.push_back(noise);
}

void Electrode::generateBetaWave() {
    // Varying the frequencies slightly
    double freq1 = 15.0 + (rand() % 3 - 1); // Random value between 14 and 16
    double freq2 = 25.0 + (rand() % 3 - 1); // Random value between 24 and 26
    int numSamples = static_cast<int>(duration * samplingFrequency);
    waveform.resize(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        double t = i / samplingFrequency;
        waveform[i] = 0.6 * sin(freq1 * 2 * M_PI * t) + 0.4 * sin(freq2 * 2 * M_PI * t);
    }
    // Adding random noise to the beta wave
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 0.1);
    double noise = distribution(generator);
    waveform.push_back(noise);
}

void Electrode::generateDeltaWave() {
    // Varying the frequencies slightly
    double freq = 2.0 + (rand() % 3 - 1); // Random value between 1 and 3
    int numSamples = static_cast<int>(duration * samplingFrequency);
    waveform.resize(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        double t = i / samplingFrequency;
        waveform[i] = 0.5 * sin(freq * 2 * M_PI * t);
    }
    // Adding random noise to the delta wave
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 0.1);
    double noise = distribution(generator);
    waveform.push_back(noise);
}

void Electrode::generateThetaWave() {
    // Varying the frequencies slightly
    double freq1 = 5.0 + (rand() % 3 - 1); // Random value between 4 and 6
    double freq2 = 7.0 + (rand() % 3 - 1); // Random value between 6 and 8
    int numSamples = static_cast<int>(duration * samplingFrequency);
    waveform.resize(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        double t = i / samplingFrequency;
        waveform[i] = 0.7 * sin(freq1 * 2 * M_PI * t) + 0.3 * sin(freq2 * 2 * M_PI * t);
    }
    // Adding random noise to the theta wave
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 0.1);
    double noise = distribution(generator);
    waveform.push_back(noise);
}

void Electrode::generateGammaWave() {
    // Varying the frequencies slightly
    double freq1 = 40.0 + (rand() % 3 - 1); // Random value between 39 and 41
    double freq2 = 70.0 + (rand() % 3 - 1); // Random value between 69 and 71
    double freq3 = 100.0 + (rand() % 3 - 1); // Random value between 99 and 101
    int numSamples = static_cast<int>(duration * samplingFrequency);
    waveform.resize(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        double t = i / samplingFrequency;
        waveform[i] = 0.8 * sin(freq1 * 2 * M_PI * t) + 0.6 * sin(freq2 * 2 * M_PI * t) + 0.4 * sin(freq3 * 2 * M_PI * t);
    }
    // Adding random noise to the gamma wave
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 0.1);
    double noise = distribution(generator);
    waveform.push_back(noise);
}



// Function to calculate the dominant frequency based on the extracted frequencies and amplitudes
double Electrode::calculateDominantFrequency() {
       // Perform Fourier Transform
       QVector<double> spectrum(waveform.size(), 0.0);
       for (unsigned long f = 0; f < waveform.size(); ++f) {
           for (unsigned long t = 0; t < waveform.size(); ++t) {
               spectrum[f] += waveform[t] * qSin(2 * M_PI * f * t / waveform.size());
           }
       }

       // Find the first three dominant frequencies and their amplitudes
       QVector<QPair<double, double>> frequenciesAndAmplitudes;
       int numDominantFrequencies = 3;
       for (int i = 0; i < numDominantFrequencies; ++i) {
           int maxIndex = 0;
           double maxValue = 0.0;
           for (int j = 0; j < spectrum.size(); ++j) {
               if (spectrum[j] > maxValue) {
                   maxIndex = j;
                   maxValue = spectrum[j];
               }
           }
           frequenciesAndAmplitudes.append(qMakePair(static_cast<double>(maxIndex), maxValue));
           // Set the amplitude at maxIndex and its neighboring frequencies to 0 to find the next dominant frequency
           for (int k = qMax(0, maxIndex - 10); k <= qMin(static_cast<int>(spectrum.size() - 1), maxIndex + 10); ++k) {
               spectrum[k] = 0.0;
           }
       }
       // Extract the frequencies and amplitudes into variables f1, f2, f3, a1, a2, a3
       double f1 = frequenciesAndAmplitudes[0].first;
       double f2 = frequenciesAndAmplitudes[1].first;
       double f3 = frequenciesAndAmplitudes[2].first;
       double a1 = frequenciesAndAmplitudes[0].second;
       double a2 = frequenciesAndAmplitudes[1].second;
       double a3 = frequenciesAndAmplitudes[2].second;

    // Calculate the dominant frequency using the provided formula
    double numerator = f1 * a1 * a1 + f2 * a2 * a2 + f3 * a3 * a3;
    double denominator = a1 * a1 + a2 * a2 + a3 * a3;

    if (denominator != 0.0) {
        return numerator / denominator;
    } else {
        // Handle division by zero
        return 0.0; // Or any default value to indicate failure
     }
}

void Electrode::plotWaveform() {
    // Create a new chart
    chart = new QtCharts::QChart();
    chart->setTitle("Brain Waveform");

    // Create a new line series
    series = new QtCharts::QLineSeries();

    // Populate the series with waveform data
    for (unsigned long i = 0; i < waveform.size(); ++i) {
        series->append(i, waveform[i]);
    }

    // Add the series to the chart
    chart->addSeries(series);

    // Create axes
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    axisX->setTitleText("Time");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Amplitude");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create a chart view to display the chart
    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Show the chart view
    chartView->show();
}




