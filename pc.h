#ifndef PC_H
#define PC_H

#include <QObject>
#include "neuresetdevice.h"
#include "dbmanager.h"

class PC : public QObject
{
    Q_OBJECT
    public:
        explicit PC(QObject *parent = nullptr);

        // functions
        void transferSessions();
        void save(const QDateTime& start, const QDateTime& end, const QMap<int, double>& before, const QMap<int, double>& after);
        QList<QString>* getData();
        void setConnect(bool);
        bool getConnect();

    private:
        bool isConnected;
        NeuresetDevice* device;
        DBManager pcDB;

    signals:

};

#endif // PC_H
