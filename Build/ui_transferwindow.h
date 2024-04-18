/********************************************************************************
** Form generated from reading UI file 'transferwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFERWINDOW_H
#define UI_TRANSFERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TransferWindow
{
public:
    QLabel *label;
    QListWidget *sessionDisplay;
    QPushButton *cancelButton;
    QPushButton *confirmButton;

    void setupUi(QDialog *TransferWindow)
    {
        if (TransferWindow->objectName().isEmpty())
            TransferWindow->setObjectName(QString::fromUtf8("TransferWindow"));
        TransferWindow->resize(900, 400);
        label = new QLabel(TransferWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(310, 10, 291, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        label->setFont(font);
        sessionDisplay = new QListWidget(TransferWindow);
        sessionDisplay->setObjectName(QString::fromUtf8("sessionDisplay"));
        sessionDisplay->setGeometry(QRect(20, 40, 861, 311));
        cancelButton = new QPushButton(TransferWindow);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(650, 360, 91, 31));
        confirmButton = new QPushButton(TransferWindow);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));
        confirmButton->setGeometry(QRect(750, 360, 130, 31));

        retranslateUi(TransferWindow);

        QMetaObject::connectSlotsByName(TransferWindow);
    } // setupUi

    void retranslateUi(QDialog *TransferWindow)
    {
        TransferWindow->setWindowTitle(QCoreApplication::translate("TransferWindow", "Confirm Transfer", nullptr));
        label->setText(QCoreApplication::translate("TransferWindow", "Session data retrieved from Neureset:", nullptr));
        cancelButton->setText(QCoreApplication::translate("TransferWindow", "Cancel", nullptr));
        confirmButton->setText(QCoreApplication::translate("TransferWindow", "Save to Database", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TransferWindow: public Ui_TransferWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFERWINDOW_H
