#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QDateTime>
#include "neuresetdevice.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void timerLabel();
    bool showMenuOptions = false; 
    EEGHeadset *eegheadset;
    NeuresetDevice* neureset;
    bool powerOn;
    bool batteryDied;
    bool showDateTimeEditActive;
    bool showTimer;
    void deviceOff();
    void deviceOn();
    void showDateTimeEdit();
    QDateTime updatedDateTime;

private slots:
    void navigateUpMenu();
    void navigateDownMenu();
    void toggleMenuVisibility();

    void onStartButtonClicked();
    void onPauseButtonClicked();
    void onStopButtonClicked();
    void onSessionLogRequested();
    void handleSelection();
    void updateProgress(int progress);
    void handleEEGHeadsetPanel();
    void handleBatteryLevelChanged();
    void powerButtonClicked();
    void updateDateTime();
    void updateDateTimeButtonClicked();
    void greenTreatmentSignal();
    void uploadPCButtonClicked();
    void showWaveformButtonClicked();
    void checkBatteryLevel();

};
#endif // MAINWINDOW_H
