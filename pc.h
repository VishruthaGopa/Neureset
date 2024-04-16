#ifndef PC_H
#define PC_H

#include <QObject>
#include "neuresetdevice.h"
#include "dbmanager.h"

class PC : public QObject
{
    Q_OBJECT
    public:
        explicit PC(NeuresetDevice*, QObject *parent = nullptr);

        // functions
        void retrieveSessions();
        void cancelCommit();
        void commitToDb();
        void save(const QDateTime& start, const QDateTime& end, const double before, const double after);

        QVector<Data*>* getData();
        void setConnect(bool);
        bool getConnect();
        QList<Session*>* getSessionLogsBuf() const;

    private:
        bool isConnected;
        NeuresetDevice* device;
        QList<Session*>* sessionLogsBuf;
        DBManager pcDB;

    signals:

};

#endif // PC_H
