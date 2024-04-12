#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QDialog>
#include "Session.h"

namespace Ui {
class TransferWindow;
}

class TransferWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransferWindow(QWidget *parent = nullptr);
    ~TransferWindow();

    void displaySessions(const QList<Session*>* sessions) const;

    bool getResponse() const;

private slots:
    void on_confirmButton_released();
    void on_cancelButton_released();

private:
    Ui::TransferWindow *ui;
    bool response;
};

#endif // TRANSFERWINDOW_H
