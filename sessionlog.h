#ifndef SESSIONLOG_H
#define SESSIONLOG_H

#include<QObject>
#include<QTimer>
#include<QList>
#include "session.h"

class SessionLog : public QObject {
    Q_OBJECT
private:
    QList<Session*> sessions;

public:
    SessionLog(QObject *parent=nullptr);
    void addSession(Session* session);
    QList<Session*> getSessionHistory() const;

signals:
    void sessionAdded(Session* session);

};

#endif // SESSIONLOG_H
