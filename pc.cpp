#include "pc.h"
#include <QtDebug>

PC::PC(QObject *parent): QObject{parent}{
    isConnected = false;
}

void PC::save(const QDateTime &s, const QDateTime &e, const QMap<int, double> &b, const QMap<int, double> &a){
    pcDB.saveSession(s, e, b, a);
}

QList<QString>* PC::getData(){
    return pcDB.getSessions();
}

bool PC::getConnect(){ return isConnected; }

void PC::setConnect(bool value ){
    isConnected = value;

    qInfo() << "PC is connecting ... " << isConnected;
}
