#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QDateTime>

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
    
private slots:
    void navigateUpMenu();
    void navigateDownMenu();
    void toggleMenuVisibility();

    void onStartButtonClicked();
    void onPauseButtonClicked();
    void onStopButtonClicked();

    void handleSelection();

};
#endif // MAINWINDOW_H
