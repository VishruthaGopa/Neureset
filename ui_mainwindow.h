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
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
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
    QLabel *contactLight;
    QLabel *treatmentLight;
    QLabel *contactLostLight;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QDateTimeEdit *dateTimeEdit;
    QPushButton *updateDateTimeButton;
    QListWidget *listWidget;
    QProgressBar *progressBar;
    QPushButton *okButton;
    QTimeEdit *timeEdit;
    QFrame *line;
    QFrame *panelFrame;
    QLabel *label_4;
    QPushButton *establishContactButton;
    QPushButton *loseContactButton;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QSlider *batterySlider;
    QToolButton *onoffButton;
    QMenuBar *menubar;
    QMenu *menuNeureset;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(890, 460);
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
        verticalLayoutWidget->setGeometry(QRect(110, 80, 291, 165));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        dateTimeEdit = new QDateTimeEdit(verticalLayoutWidget);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setEnabled(false);

        verticalLayout->addWidget(dateTimeEdit);

        updateDateTimeButton = new QPushButton(verticalLayoutWidget);
        updateDateTimeButton->setObjectName(QString::fromUtf8("updateDateTimeButton"));
        updateDateTimeButton->setEnabled(true);

        verticalLayout->addWidget(updateDateTimeButton);

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
        timeEdit = new QTimeEdit(frame);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(180, 310, 118, 26));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(610, 10, 16, 391));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        panelFrame = new QFrame(centralwidget);
        panelFrame->setObjectName(QString::fromUtf8("panelFrame"));
        panelFrame->setGeometry(QRect(630, 10, 251, 371));
        panelFrame->setStyleSheet(QString::fromUtf8("background-color: #f5f5f5;"));
        panelFrame->setFrameShape(QFrame::StyledPanel);
        panelFrame->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(panelFrame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 10, 101, 17));
        QFont font4;
        font4.setFamily(QString::fromUtf8("DejaVu Sans"));
        font4.setBold(true);
        font4.setWeight(75);
        label_4->setFont(font4);
        establishContactButton = new QPushButton(panelFrame);
        establishContactButton->setObjectName(QString::fromUtf8("establishContactButton"));
        establishContactButton->setGeometry(QRect(10, 40, 131, 25));
        loseContactButton = new QPushButton(panelFrame);
        loseContactButton->setObjectName(QString::fromUtf8("loseContactButton"));
        loseContactButton->setGeometry(QRect(10, 70, 101, 25));
        label_5 = new QLabel(panelFrame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 130, 101, 17));
        label_5->setFont(font4);
        label_3 = new QLabel(panelFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(200, 180, 41, 17));
        label = new QLabel(panelFrame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 160, 62, 17));
        label_2 = new QLabel(panelFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 180, 31, 17));
        batterySlider = new QSlider(panelFrame);
        batterySlider->setObjectName(QString::fromUtf8("batterySlider"));
        batterySlider->setGeometry(QRect(80, 160, 160, 16));
        batterySlider->setMaximum(100);
        batterySlider->setOrientation(Qt::Horizontal);
        batterySlider->setTickPosition(QSlider::TicksBelow);
        batterySlider->setTickInterval(50);
        onoffButton = new QToolButton(panelFrame);
        onoffButton->setObjectName(QString::fromUtf8("onoffButton"));
        onoffButton->setGeometry(QRect(10, 220, 161, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 890, 22));
        menuNeureset = new QMenu(menubar);
        menuNeureset->setObjectName(QString::fromUtf8("menuNeureset"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNeureset->menuAction());

        retranslateUi(MainWindow);

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
        contactLight->setText(QString());
        treatmentLight->setText(QString());
        contactLostLight->setText(QString());
        updateDateTimeButton->setText(QCoreApplication::translate("MainWindow", "Update Date and Time", nullptr));
        okButton->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "EEG HeadSet", nullptr));
        establishContactButton->setText(QCoreApplication::translate("MainWindow", "Establish Contact", nullptr));
        loseContactButton->setText(QCoreApplication::translate("MainWindow", "Lose Contact", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Admin", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Battery", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "0%", nullptr));
        onoffButton->setText(QCoreApplication::translate("MainWindow", "Power ON/Power OFF", nullptr));
        menuNeureset->setTitle(QCoreApplication::translate("MainWindow", "Neureset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
