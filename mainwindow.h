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
    void initializeDateTimeLabel();
    bool showMenuOptions = false; 
    void greenTreatmentSignal();
    EEGHeadset *eegheadset;
    NeuresetDevice* neureset;
    
private slots:
    void navigateUpMenu();
    void navigateDownMenu();
    void toggleMenuVisibility();

    void onStartButtonClicked();
    void onPauseButtonClicked();
    void onStopButtonClicked();

    void handleSelection();
    void updateProgress(int progress);
    void handleEEGHeadsetPanel();

};
#endif // MAINWINDOW_H
