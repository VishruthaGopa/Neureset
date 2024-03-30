#ifndef COUNTER_H
#define COUNTER_H
#include<QObject>
#include<QTimer>

class Counter : public QObject {
    Q_OBJECT
private:
    QTimer* timer;
    bool paused;
    int duration; // Duration of the session in seconds
    int timeRemaining; // Time remaining in the session in seconds

public:
    Counter(int durationSeconds = 60, QObject* parent = nullptr);

    // Function to start the session
    void start();

    // Function to pause the session
    void pause();

    // Function to resume the session
    void resume();

    // Function to end the session
    void end();

signals:
    void sessionStarted();
    void sessionPaused();
    void sessionResumed();
    void sessionEnded();
    void timeUpdated(int secondsRemaining);

private slots:
    void updateTime();
};




#endif // COUNTER_H
