#ifndef EEGHEADSET_H
#define EEGHEADSET_H
#include<QObject>
#include<QTimer>
#include "electrode.h"

class EEGHeadset : public QObject {
    Q_OBJECT
private:
    QVector<Electrode*> electrodeSites;

public:
    EEGHeadset(QObject* parent = nullptr);

    // Destructor to free memory allocated for electrodes
    ~EEGHeadset();

    // Function to get an electrode site by index
    Electrode* getElectrodeSite(int index) const;
public slots:
    void handleTreatmentApplied(Session *session);
signals:
    void newSession(Session *session);
};



#endif // EEGHEADSET_H
