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
        PCWindow(QWidget *parent = nullptr);
        ~PCWindow();

        void setUpTable();

    private:
        Ui::PCWindow *ui;
        PC* pc;
        DataModel model;

    private slots:
        void handleExample();
        void handleConnect();

};
#endif // PCWINDOW_H
