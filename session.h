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
    QMap<int, double> beforeBaseline;
    QMap<int, double> afterBaseline;
;
public:
    Session(QObject *parent=nullptr);
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
    QMap<int, double> getBeforeBaseline() const;
    void setBeforeBaseline(const QMap<int, double>& baseline);
    QMap<int, double> getAfterBaseline() const;
    void setAfterBaseline(const QMap<int, double>& baseline);
};

#endif // SESSION_H
