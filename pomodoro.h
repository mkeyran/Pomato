#ifndef POMODORO_H
#define POMODORO_H
#include <QObject>
#include <QTimer>
enum class State {STOPPED, ACTIVE, SHORT_BREAK, LONG_BREAK, PAUSED};

class Pomodoro : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(State prevState READ prevState WRITE setPrevState)
    Q_PROPERTY(quint32 pomodoroDuration READ pomodoroDuration WRITE setPomodoroDuration NOTIFY pomodoroDurationChanged)
    Q_PROPERTY(quint32 shortBreakDuration READ shortBreakDuration WRITE setShortBreakDuration NOTIFY shortBreakDurationChanged)
    Q_PROPERTY(quint32 longBreakDuration READ longBreakDuration WRITE setLongBreakDuration NOTIFY longBreakDurationChanged)
    Q_PROPERTY(bool pauseIsAllowed READ pauseIsAllowed WRITE setPauseIsAllowed NOTIFY pauseIsAllowedChanged)
    Q_PROPERTY(bool autoContinue READ autoContinue WRITE setAutoContinue NOTIFY autoContinueChanged)
    Q_PROPERTY(qint32 remaining READ remaining NOTIFY remainingChanged)
    Q_PROPERTY(qint32 passed READ passed NOTIFY passedChanged)
    State m_state;

public:
    explicit Pomodoro(QObject *parent = 0);
    explicit Pomodoro(quint32 pomodoroDuration,
                      quint32 shortBreakDuration,
                      quint32 longBreakDuration,
                      QObject *parent = 0);

State state() const;

quint32 pomodoroDuration() const;

quint32 shortBreakDuration() const;

quint32 longBreakDuration() const;

bool pauseIsAllowed() const;

bool autoContinue() const;

qint32 passed() const;

qint32 remaining() const;

State prevState() const;

signals:

void stateChanged(State state);

void pomodoroDurationChanged(quint32 pomodoroDuration);

void shortBreakDurationChanged(quint32 shortBreakDuration);

void longBreakDurationChanged(quint32 longBreakDuration);

void pauseIsAllowedChanged(bool pauseIsAllowed);

void autoContinueChanged(bool autoContinue);

void passedChanged(qint32 passed);

void remainingChanged(qint32 remaining);


public slots:
void setState(State state);

void setPomodoroDuration(quint32 pomodoroDuration);

void setShortBreakDuration(quint32 shortBreakDuration);

void setLongBreakDuration(quint32 longBreakDuration);

void setPauseIsAllowed(bool pauseIsAllowed);

void start(State state = State::ACTIVE);
void stop();
void pause();

void setAutoContinue(bool autoContinue);
qint32 remainingTime() const;
qint32 passedTime() const;

void nextState();

void notifyRemaining();

void setPrevState(State prevState);

private:
quint32 m_pomodoroDuration;
quint32 m_shortBreakDuration;
quint32 m_longBreakDuration;
bool m_pauseIsAllowed;
QTimer timer;
QTimer passed_timer;
bool m_autoContinue;
quint8 pomodorosAmount;
quint32 pauseRemaining;
qint32 m_passed;
qint32 m_remaining;
State m_prevState;
};

#endif // POMODORO_H
