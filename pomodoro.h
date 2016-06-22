#ifndef POMODORO_H
#define POMODORO_H
#include <QObject>
#include <QTimer>

enum class Status {STOPPED, ACTIVE, SHORT_BREAK, LONG_BREAK, PAUSED};

class Pomodoro : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(quint32 pomodoroDuration READ pomodoroDuration WRITE setPomodoroDuration NOTIFY pomodoroDurationChanged)
    Q_PROPERTY(quint32 shortBreakDuration READ shortBreakDuration WRITE setShortBreakDuration NOTIFY shortBreakDurationChanged)
    Q_PROPERTY(quint32 longBreakDuration READ longBreakDuration WRITE setLongBreakDuration NOTIFY longBreakDurationChanged)
    Q_PROPERTY(bool pauseIsAllowed READ pauseIsAllowed WRITE setPauseIsAllowed NOTIFY pauseIsAllowedChanged)
    Q_PROPERTY(bool autoContinue READ autoContinue WRITE setAutoContinue NOTIFY autoContinueChanged)
    Q_PROPERTY(qint32 remaining READ remaining NOTIFY remainingChanged)
    Q_PROPERTY(qint32 passed READ passed NOTIFY passedChanged)
    Status m_status;

public:
    explicit Pomodoro(QObject *parent = 0);
    explicit Pomodoro(quint32 pomodoroDuration,
                      quint32 shortBreakDuration,
                      quint32 longBreakDuration,
                      QObject *parent = 0);

Status status() const;

quint32 pomodoroDuration() const;

quint32 shortBreakDuration() const;

quint32 longBreakDuration() const;

bool pauseIsAllowed() const;

bool autoContinue() const;

qint32 passed() const;

qint32 remaining() const;

signals:

void statusChanged(Status status);

void pomodoroDurationChanged(quint32 pomodoroDuration);

void shortBreakDurationChanged(quint32 shortBreakDuration);

void longBreakDurationChanged(quint32 longBreakDuration);

void pauseIsAllowedChanged(bool pauseIsAllowed);

void autoContinueChanged(bool autoContinue);

void passedChanged(qint32 passed);

void remainingChanged(qint32 remaining);

public slots:
void setStatus(Status status);

void setPomodoroDuration(quint32 pomodoroDuration);

void setShortBreakDuration(quint32 shortBreakDuration);

void setLongBreakDuration(quint32 longBreakDuration);

void setPauseIsAllowed(bool pauseIsAllowed);

void start(Status state = Status::ACTIVE);
void stop();
void pause();

void setAutoContinue(bool autoContinue);
qint32 remainingTime() const;
qint32 passedTime() const;

void nextStatus();

void notifyRemaining();

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
};

#endif // POMODORO_H
