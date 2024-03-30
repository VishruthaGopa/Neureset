#include "pc.h"
#include <QtDebug>

PC::PC(QObject *parent): QObject{parent}{
    isConnected = false;
}

void PC::saveSession(){
    // data structure??
    // text file maybe
}

bool PC::getConnect(){ return isConnected; }

void PC::setConnect(bool value ){
    isConnected = value;

    qInfo() << "PC is connecting ... " << isConnected;
}
