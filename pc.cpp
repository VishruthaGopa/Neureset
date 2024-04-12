#include "pc.h"
#include <QtDebug>

PC::PC(QObject *parent): QObject{parent}{
    isConnected = false;
    sessionLogsBuf = nullptr;
}

void PC::retrieveSessions(QList<Session*>* sessions) {
    // store sessions in temporary buffer, retrieved from Neureset device or from provided argument
    sessionLogsBuf = new QList<Session*>;

    if (sessions != nullptr) {
        *sessionLogsBuf = *sessions;
    }
    else {
        *sessionLogsBuf = device->getSessionLog()->getSessionHistory();
    }
}

void PC::cancelCommit() {
    delete sessionLogsBuf;
    sessionLogsBuf = nullptr;
}

void PC::commitToDb() {
    // save each session to the database
    for (int i = 0; i < (*sessionLogsBuf).count(); i++) {
        save((*sessionLogsBuf)[i]->getStartTime(), (*sessionLogsBuf)[i]->getEndTime(), (*sessionLogsBuf)[i]->getBeforeBaseline(), (*sessionLogsBuf)[i]->getAfterBaseline());
    }
    delete sessionLogsBuf;
    sessionLogsBuf = nullptr;
}

void PC::save(const QDateTime &s, const QDateTime &e, const double b, const double a){
    pcDB.saveSession(s, e, b, a);
}

QVector<Data*>* PC::getData(){
    return pcDB.getSessions();
}

bool PC::getConnect(){ return isConnected; }

QList<Session*>* PC::getSessionLogsBuf() const { return sessionLogsBuf; }

void PC::setConnect(bool value ){
    isConnected = value;

    qInfo() << "PC is connecting ... " << isConnected;
}
