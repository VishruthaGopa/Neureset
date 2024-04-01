#ifndef EEGHEADSET_H
#define EEGHEADSET_H
#include<QObject>
#include<QTimer>
#include <QThread>
#include "session.h"
#include "electrode.h"

class EEGHeadset : public QObject {
    Q_OBJECT
private:
    struct Complex {
        double real;
        double imag;

        Complex(double r, double i) : real(r), imag(i) {}
        Complex() : real(0), imag(0) {}
    };
    QVector<Electrode*> electrodeSites;
    QVector<double> baselineFrequencies;
    QVector<double> afterFrequencies;
    Session* session;
    int currElectrode;

    /*
        This is the implementation of the Fast Fourier Transform (FFT) algorithm.
        It recursively divides the input vector into even and odd parts, performs FFT on each part, and then combines the results.
        It calculates the FFT by multiplying the complex numbers with appropriate twiddle factors and combining them to obtain the result.
        The base case of recursion is when the input size is 1 or less, in which case it returns the input vector as-is.
    */
    QVector<Complex> fft(const QVector<Complex> &x) {
        int N = x.size();
        if (N <= 1)
            return x;

        QVector<Complex> even(N / 2), odd(N / 2);
        for (int i = 0; i < N / 2; ++i) {
            even[i] = x[i * 2];
            odd[i] = x[i * 2 + 1];
        }

        QVector<Complex> evenResult = fft(even);
        QVector<Complex> oddResult = fft(odd);

        QVector<Complex> result(N);
        for (int k = 0; k < N / 2; ++k) {
            double theta = -2 * M_PI * k / N;
            Complex t;
            t.real = cos(theta) * oddResult[k].real - sin(theta) * oddResult[k].imag;
            t.imag = cos(theta) * oddResult[k].imag + sin(theta) * oddResult[k].real;
            result[k].real = evenResult[k].real + t.real;
            result[k].imag = evenResult[k].imag + t.imag;
            result[k + N / 2].real = evenResult[k].real - t.real;
            result[k + N / 2].imag = evenResult[k].imag - t.imag;
        }
        return result;
    }


public:
    EEGHeadset(QObject* parent = nullptr);

    // Destructor to free memory allocated for electrodes
    ~EEGHeadset();

    // Function to get an electrode site by index
    Electrode* getElectrodeSite(int index) const;
    void createNewSession();
    bool treatNext();
    void startMeasurement();
    void handleBaseline(double frequency);
    void handleTreatmentApplied(double frequency);


    // Function to calculate FFT and return dominant frequency
    double calculateDominantFrequency(const QVector<double> &frequencies);


signals:
    void newSession(Session *session);
};



#endif // EEGHEADSET_H
