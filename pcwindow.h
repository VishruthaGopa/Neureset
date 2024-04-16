#ifndef PCWINDOW_H
#define PCWINDOW_H

#include <QMainWindow>
#include "pc.h"
#include "datamodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PCWindow; }
QT_END_NAMESPACE

class PCWindow : public QMainWindow
{
    Q_OBJECT

    public:
        PCWindow(NeuresetDevice*, QWidget *parent = nullptr);
        ~PCWindow();

        void setUpTable();

    private:
        Ui::PCWindow *ui;
        PC* pc;
        DataModel model;
        NeuresetDevice* device;

    private slots:
        void handleConnect();
        void handleTransfer();

};
#endif // PCWINDOW_H
