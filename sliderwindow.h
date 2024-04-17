#ifndef SLIDERWINDOW_H
#define SLIDERWINDOW_H

#include <QMainWindow>
#include "electrode.h"

namespace Ui {
class SliderWindow;
}

class SliderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SliderWindow(QVector<Electrode*> electrodes, QWidget *parent = nullptr);
    ~SliderWindow();
    void showElectrode(int index);
    void showNextElectrode();
    void showPrevElectrode();

private:
    Ui::SliderWindow *ui;
    int currentElectrodeIndex;
    QVector<Electrode*> electrodes;
    bool showingBeforeWaveform;



};

#endif // SLIDERWINDOW_H
