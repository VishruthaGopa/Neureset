#include "pc.h"
#include <QtDebug>

PC::PC(QObject *parent): QObject{parent}{
    isConnected = false;
}

void PC::transferSessions() {
    // get session history from Neureset device and save each session to db

    QList<Session*> sessionLogs;
    sessionLogs = device->getSessionLog()->getSessionHistory();

    for (int i = 0; i < sessionLogs.count(); i++) {
        save(sessionLogs[i]->getStartTime(), sessionLogs[i]->getEndTime(), sessionLogs[i]->getBeforeBaseline(), sessionLogs[i]->getAfterBaseline());
    }
}

void PC::save(const QDateTime &s, const QDateTime &e, const QMap<int, double> &b, const QMap<int, double> &a){
    pcDB.saveSession(s, e, b, a);
}

QVector<Data*>* PC::getData(){
    return pcDB.getSessions();
}

bool PC::getConnect(){ return isConnected; }

void PC::setConnect(bool value ){
    isConnected = value;

    qInfo() << "PC is connecting ... " << isConnected;
}
