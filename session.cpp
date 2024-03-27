#include "session.h"

Session::Session(QObject *parent):QObject(parent){}


QDateTime Session::getStartTime() const { return startTime; }

QDateTime Session::getEndTime() const { return endTime; }

QMap<int, double> Session::getBeforeBaseline() const { return beforeBaseline; }

void Session::setBeforeBaseline(const QMap<int, double>& baseline) { beforeBaseline = baseline; }

QMap<int, double> Session::getAfterBaseline() const { return afterBaseline; }

void Session::setAfterBaseline(const QMap<int, double>& baseline) { afterBaseline = baseline; }
