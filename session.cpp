#include "session.h"

Session::Session(QObject *parent):QObject(parent){}


QDateTime Session::getStartTime() const { return startTime; }

QDateTime Session::getEndTime() const { return endTime; }

double Session::getBeforeBaseline() const { return beforeBaseline; }

void Session::setBeforeBaseline(double baseline) { beforeBaseline = baseline; }

double Session::getAfterBaseline() const { return afterBaseline; }

void Session::setAfterBaseline(double baseline) { afterBaseline = baseline; }

void Session::startTimer(){startTime=QDateTime::currentDateTime();}

void Session::endTimer(){endTime=QDateTime::currentDateTime();}

void Session::startTimer(const QDateTime &currentTime) { startTime = currentTime;}

void Session::endTimer(const QDateTime &currentTime) { endTime = currentTime;}
