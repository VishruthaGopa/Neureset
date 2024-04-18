/********************************************************************************
** Form generated from reading UI file 'pcwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCWINDOW_H
#define UI_PCWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PCWindow
{
public:
    QWidget *centralwidget;
    QCheckBox *checkBox;
    QTableView *table;
    QPushButton *transferButton;
    QMenuBar *menubar;
    QMenu *menuSession_History;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PCWindow)
    {
        if (PCWindow->objectName().isEmpty())
            PCWindow->setObjectName(QString::fromUtf8("PCWindow"));
        PCWindow->resize(800, 600);
        centralwidget = new QWidget(PCWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(20, 522, 161, 31));
        table = new QTableView(centralwidget);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(20, 20, 761, 491));
        transferButton = new QPushButton(centralwidget);
        transferButton->setObjectName(QString::fromUtf8("transferButton"));
        transferButton->setEnabled(false);
        transferButton->setGeometry(QRect(670, 520, 111, 31));
        PCWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PCWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuSession_History = new QMenu(menubar);
        menuSession_History->setObjectName(QString::fromUtf8("menuSession_History"));
        PCWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PCWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PCWindow->setStatusBar(statusbar);

        menubar->addAction(menuSession_History->menuAction());

        retranslateUi(PCWindow);

        QMetaObject::connectSlotsByName(PCWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PCWindow)
    {
        PCWindow->setWindowTitle(QCoreApplication::translate("PCWindow", "PCWindow", nullptr));
        checkBox->setText(QCoreApplication::translate("PCWindow", "NeureSet Connected", nullptr));
        transferButton->setText(QCoreApplication::translate("PCWindow", "Transfer Data", nullptr));
        menuSession_History->setTitle(QCoreApplication::translate("PCWindow", "Therapy History", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PCWindow: public Ui_PCWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCWINDOW_H
