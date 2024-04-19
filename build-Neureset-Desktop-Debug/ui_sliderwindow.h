/********************************************************************************
** Form generated from reading UI file 'sliderwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDERWINDOW_H
#define UI_SLIDERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SliderWindow
{
public:
    QWidget *centralwidget;
    QPushButton *nextButton;
    QGraphicsView *graphicsView;
    QPushButton *prevButton;
    QLabel *electrodeLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SliderWindow)
    {
        if (SliderWindow->objectName().isEmpty())
            SliderWindow->setObjectName(QString::fromUtf8("SliderWindow"));
        SliderWindow->resize(920, 600);
        centralwidget = new QWidget(SliderWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(799, 460, 83, 25));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(129, 80, 641, 401));
        prevButton = new QPushButton(centralwidget);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        prevButton->setGeometry(QRect(29, 460, 83, 25));
        electrodeLabel = new QLabel(centralwidget);
        electrodeLabel->setObjectName(QString::fromUtf8("electrodeLabel"));
        electrodeLabel->setGeometry(QRect(130, 60, 411, 20));
        SliderWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SliderWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 920, 22));
        SliderWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SliderWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SliderWindow->setStatusBar(statusbar);

        retranslateUi(SliderWindow);

        QMetaObject::connectSlotsByName(SliderWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SliderWindow)
    {
        SliderWindow->setWindowTitle(QCoreApplication::translate("SliderWindow", "MainWindow", nullptr));
        nextButton->setText(QCoreApplication::translate("SliderWindow", "Next", nullptr));
        prevButton->setText(QCoreApplication::translate("SliderWindow", "Last", nullptr));
        electrodeLabel->setText(QCoreApplication::translate("SliderWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SliderWindow: public Ui_SliderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDERWINDOW_H
