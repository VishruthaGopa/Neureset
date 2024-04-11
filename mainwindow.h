#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QDateTime>
#include "neuresetdevice.h"

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
    void greenTreatmentSignal();
    EEGHeadset *eegheadset;
    NeuresetDevice* neureset;
    bool powerOn;
    void deviceOff();
    void deviceOn();
    
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
};
#endif // MAINWINDOW_H
