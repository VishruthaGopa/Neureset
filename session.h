#ifndef SESSION_H
#define SESSION_H
#include<QObject>
#include<QTimer>
#include<QTime>
#include <QMap>

class Session : public QObject {
    Q_OBJECT
private:
    QDateTime startTime;
    QDateTime endTime;
    double beforeBaseline;
    double afterBaseline;
;
public:
    Session(QObject *parent=nullptr);
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
    double getBeforeBaseline() const;
    void setBeforeBaseline(double baseline);
    double getAfterBaseline() const;
    void setAfterBaseline(double baseline);
    void startTimer();
    void endTimer();
};

#endif // SESSION_H
