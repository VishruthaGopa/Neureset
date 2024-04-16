#include "dbmanager.h"

const QString DBManager::DATE_FORMAT = "yyyy-MM-dd hh:mm:ss";

DBManager::DBManager(){
    db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("neureset.db");
    // db.setDatabaseName("test.db");

    qInfo("Instantiating database...");

    // error checking
    if (!db.open()) {
        qInfo("ERROR: could not open data.");
        return;
    }
    else{
        qInfo("Opening database...");
    }

    qInfo("Instiating successful.");

    if(!initDb()){
        qInfo("ERROR: could not initalize database.");
        return;
    }
    else{
        qInfo("Initating database...");
    }
}

bool DBManager::initDb(){

    qInfo("Calling instantiating function...");

    // begin transaction query
    db.transaction();

    QSqlQuery q;
    // database contains time start, time end, average before baseline and average after baseline
    q.exec("CREATE TABLE IF NOT EXISTS sessions ( start_time TEXT NOT NULL, end_time TEXT NOT NULL, before_baseline DOUBLE NOT NULL, after_baseline DOUBLE NOT NULL,"
           "UNIQUE (start_time, end_time, before_baseline, after_baseline));");

    return db.commit();
}

bool DBManager::saveSession(const QDateTime &start, const QDateTime &end, const double before, const double after){
    db.transaction();

    QSqlQuery q;

    // prepares a format to add to database
    q.prepare("INSERT INTO sessions ( start_time, end_time, before_baseline, after_baseline ) VALUES (:start, :end, :before, :after);");

    q.bindValue( ":start" , start.toString(DATE_FORMAT));
    q.bindValue(":end", end.toString(DATE_FORMAT));
    q.bindValue(":before", QString::number(before, 'f', 3) );
    q.bindValue(":after", QString::number(after, 'f', 3) );

    q.exec();

    return db.commit();

}

//QVector<QString>* DBManager::getSessions() const{
QVector<Data*>* DBManager::getSessions() const{
//    QVector<QString>* retVal = new QVector<QString>;

    QVector<Data*>* retVal = new QVector<Data*>;

    QSqlQuery q;
    q.exec("SELECT * FROM sessions");

    while(q.next()){

        Data* inVal = new Data;

        inVal->startTime = q.value(0).toString();
        inVal->endTime = q.value(1).toString();
        inVal->beforeFreq = q.value(2).toString();
        inVal->afterFreq = q.value(3).toString();

        retVal->append( inVal );

    }

    return retVal;
}

bool DBManager::deleteData(){
    QSqlQuery q;
    q.prepare("DELETE FROM sessions");
    return q.exec();
}

void DBManager::close(){
    db.close();
}

int DBManager::countSessions() const{
    QSqlQuery q;
    q.exec("SELECT COUNT(*) FROM sessions");

    q.next();

    int retVal = q.value(0).toInt();

    qInfo("RETURNED ROWS: %2d", retVal);

    return retVal;
}
