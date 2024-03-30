/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QPushButton *menuButton;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *pauseButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QToolButton *batteryIndicator;
    QToolButton *onoffButton;
    QLabel *contactLight;
    QLabel *treatmentLight;
    QLabel *contactLostLight;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QProgressBar *progressBar;
    QPushButton *okButton;
    QTabWidget *tabWidget;
    QWidget *headsetPanel;
    QPushButton *loseContactButton;
    QPushButton *establishContactButton;
    QWidget *adminPanel;
    QMenuBar *menubar;
    QMenu *menuNeureset;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(882, 480);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 10, 581, 371));
        frame->setStyleSheet(QString::fromUtf8("background-color: #f5f5f5;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        menuButton = new QPushButton(frame);
        menuButton->setObjectName(QString::fromUtf8("menuButton"));
        menuButton->setGeometry(QRect(110, 40, 51, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans"));
        font.setPointSize(12);
        menuButton->setFont(font);
        upButton = new QPushButton(frame);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setGeometry(QRect(440, 120, 51, 25));
        upButton->setFont(font);
        downButton = new QPushButton(frame);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setGeometry(QRect(440, 160, 51, 25));
        downButton->setFont(font);
        pauseButton = new QPushButton(frame);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setGeometry(QRect(160, 250, 51, 25));
        startButton = new QPushButton(frame);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(230, 250, 51, 25));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans"));
        font1.setPointSize(13);
        startButton->setFont(font1);
        stopButton = new QPushButton(frame);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(300, 250, 41, 25));
        stopButton->setFont(font1);
        batteryIndicator = new QToolButton(frame);
        batteryIndicator->setObjectName(QString::fromUtf8("batteryIndicator"));
        batteryIndicator->setGeometry(QRect(530, 330, 29, 24));
        onoffButton = new QToolButton(frame);
        onoffButton->setObjectName(QString::fromUtf8("onoffButton"));
        onoffButton->setGeometry(QRect(530, 10, 29, 24));
        contactLight = new QLabel(frame);
        contactLight->setObjectName(QString::fromUtf8("contactLight"));
        contactLight->setGeometry(QRect(10, 0, 16, 31));
        contactLight->setStyleSheet(QString::fromUtf8("background-color: #e4f0fa;"));
        treatmentLight = new QLabel(frame);
        treatmentLight->setObjectName(QString::fromUtf8("treatmentLight"));
        treatmentLight->setGeometry(QRect(30, 0, 16, 31));
        treatmentLight->setStyleSheet(QString::fromUtf8("background-color: #ddf3c8;"));
        contactLostLight = new QLabel(frame);
        contactLostLight->setObjectName(QString::fromUtf8("contactLostLight"));
        contactLostLight->setGeometry(QRect(50, 0, 16, 31));
        contactLostLight->setStyleSheet(QString::fromUtf8("background-color: #ffcccf;"));
        verticalLayoutWidget = new QWidget(frame);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(110, 80, 291, 161));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Liberation Mono"));
        font2.setPointSize(13);
        font2.setBold(false);
        font2.setWeight(50);
        listWidget->setFont(font2);

        verticalLayout->addWidget(listWidget);

        progressBar = new QProgressBar(verticalLayoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        okButton = new QPushButton(frame);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(500, 140, 30, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("DejaVu Sans"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        okButton->setFont(font3);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(610, 10, 261, 371));
        headsetPanel = new QWidget();
        headsetPanel->setObjectName(QString::fromUtf8("headsetPanel"));
        loseContactButton = new QPushButton(headsetPanel);
        loseContactButton->setObjectName(QString::fromUtf8("loseContactButton"));
        loseContactButton->setGeometry(QRect(20, 60, 101, 25));
        establishContactButton = new QPushButton(headsetPanel);
        establishContactButton->setObjectName(QString::fromUtf8("establishContactButton"));
        establishContactButton->setGeometry(QRect(20, 20, 131, 25));
        tabWidget->addTab(headsetPanel, QString());
        adminPanel = new QWidget();
        adminPanel->setObjectName(QString::fromUtf8("adminPanel"));
        tabWidget->addTab(adminPanel, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 882, 22));
        menuNeureset = new QMenu(menubar);
        menuNeureset->setObjectName(QString::fromUtf8("menuNeureset"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNeureset->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        menuButton->setText(QCoreApplication::translate("MainWindow", "\342\230\260", nullptr));
        upButton->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        downButton->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "\342\226\220\342\226\220", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\342\226\266", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "\342\227\274", nullptr));
        batteryIndicator->setText(QCoreApplication::translate("MainWindow", "\342\232\241", nullptr));
        onoffButton->setText(QCoreApplication::translate("MainWindow", "I/O", nullptr));
        contactLight->setText(QString());
        treatmentLight->setText(QString());
        contactLostLight->setText(QString());
        okButton->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        loseContactButton->setText(QCoreApplication::translate("MainWindow", "Lose Contact", nullptr));
        establishContactButton->setText(QCoreApplication::translate("MainWindow", "Establish Contact", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(headsetPanel), QCoreApplication::translate("MainWindow", "EEG Headset", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(adminPanel), QCoreApplication::translate("MainWindow", "Admin", nullptr));
        menuNeureset->setTitle(QCoreApplication::translate("MainWindow", "Neureset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
