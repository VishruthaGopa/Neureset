#include "transferwindow.h"
#include "ui_transferwindow.h"

TransferWindow::TransferWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferWindow)
{
    ui->setupUi(this);
}

TransferWindow::~TransferWindow()
{
    delete ui;
}

bool TransferWindow::getResponse() const { return response; }

void TransferWindow::displaySessions(const QList<Session*>* sessions) const {
    for (Session* session : *sessions) {
        QString s = QString("%1        %2        %3        %4").arg(session->getStartTime().toString(), session->getEndTime().toString(), QString::number(session->getBeforeBaseline()), QString::number(session->getAfterBaseline()));
        new QListWidgetItem(s, ui->sessionDisplay);
    }
}

void TransferWindow::on_confirmButton_released() {
    qInfo("Transfer confirmed. Saving to database...");
    response = true;
    done(1);
}


void TransferWindow::on_cancelButton_released() {
    qInfo("Transfer cancelled");
    response = false;
    done(0);
}

