#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QVariant>

#include "session.h"

class DBManager
{
    public:
        const QString DB_PATH = "/database/test.db";
        static const QString DATE_FORMAT;

        DBManager();
        bool saveSession(const QDateTime& s, const QDateTime& e, const QMap<int,double>& b, const QMap<int,double>& a);
        QList<QString>* getSessions();
        bool deleteData();

    private:
        QSqlDatabase db;
        bool initDb();
};

#endif // DBMANAGER_H
