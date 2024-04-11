#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QVariant>
#include <QAbstractTableModel>

#include "session.h"

struct Data{
    public:
        QString startTime;
        QString endTime;
        QString beforeFreq;     // stores the average of all before frequencies
        QString afterFreq;      // stores the average of all after frequencies
};

class DBManager
{
    public:
        const QString DB_PATH = "/database/test.db";
        static const QString DATE_FORMAT;

        DBManager();
        bool saveSession(const QDateTime& s, const QDateTime& e, const QMap<int,double>& b, const QMap<int,double>& a);
        QVector<Data*>* getSessions() const;
        bool deleteData();
        void close();
        int countSessions() const;

    private:
        QSqlDatabase db;
        bool initDb();
};

#endif // DBMANAGER_H
