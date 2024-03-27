#include "counter.h"

Counter::Counter(int durationSeconds, QObject* parent) : QObject(parent), paused(false),duration(durationSeconds), timeRemaining(durationSeconds) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Counter::updateTime);
}

// Function to start the session
void Counter::start() {
    timeRemaining = duration;
    paused = false;
    emit sessionStarted();
    timer->start(1000); // Start the timer with a 1-second interval
}

// Function to pause the session
void Counter::pause() {
    if (!paused) {
        paused = true;
        emit sessionPaused();
        timer->stop(); // Stop the timer
    }
}

// Function to resume the session
void Counter::resume() {
    if (paused) {
        paused = false;
        emit sessionResumed();
        timer->start(1000); // Start the timer with a 1-second interval
    }
}

// Function to end the session
void Counter::end() {
    paused = false;
    timer->stop();
    emit sessionEnded();
}

void Counter::updateTime() {
    timeRemaining--;
    if (timeRemaining <= 0) {
        end();
    } else {
        emit timeUpdated(timeRemaining);
    }
}

