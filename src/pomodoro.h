#ifndef POMODORO_H
#define POMODORO_H
#include <QObject>
#include <QTimer>
#include <settings.h>
#include <memory.h>
enum class State {STOPPED, ACTIVE, SHORT_BREAK, LONG_BREAK, PAUSED};

class Pomodoro : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(State prevState READ prevState WRITE setPrevState)
    Q_PROPERTY(qint32 remaining READ remaining NOTIFY remainingChanged)
    Q_PROPERTY(qint32 passed READ passed NOTIFY passedChanged)
    State m_state;

public:
    explicit Pomodoro(std::shared_ptr<Settings> settings, QObject *parent = 0);

State state() const;

qint32 passed() const;

qint32 remaining() const;

State prevState() const;

signals:

void stateChanged(State state);

void passedChanged(qint32 passed);

void remainingChanged(qint32 remaining);


public slots:
void setState(State state);

void start(State state = State::ACTIVE);
void stop();
void pause();

qint32 remainingTime() const;
qint32 passedTime() const;

void nextState();

void notifyRemaining();

void setPrevState(State prevState);

private:
QTimer timer;
QTimer passed_timer;
quint8 pomodorosAmount;
quint32 pauseRemaining;
qint32 m_passed;
qint32 m_remaining;
State m_prevState;
std::shared_ptr<Settings> settings;
};

#endif // POMODORO_H
