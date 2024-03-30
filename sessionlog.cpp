#include "sessionlog.h"

SessionLog::SessionLog(QObject *parent):QObject(parent){}

void SessionLog::addSession(Session* session) { sessions.append(session); }

QList<Session*> SessionLog::getSessionHistory() const { return sessions; }
