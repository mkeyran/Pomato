#include "pomodoro.h"
#include <cmath>

Pomodoro::Pomodoro(QObject *parent) : Pomodoro(1000*60*25,1000*60*5,1000*60*15,parent)
{
}

Pomodoro::Pomodoro(quint32 pomodoroDuration, quint32 shortBreakDuration, quint32 longBreakDuration, QObject *parent)
    : QObject(parent),
      m_status(Status::STOPPED),
      m_pomodoroDuration(pomodoroDuration),
      m_shortBreakDuration(shortBreakDuration),
      m_longBreakDuration(longBreakDuration),
      m_pauseIsAllowed(true),
      m_autoContinue(true),
      pomodorosAmount(0)
{
//    timer.setTimerType(Qt::VeryCoarseTimer);
    timer.setSingleShot(true);
    connect(&timer,SIGNAL(timeout()),this,SLOT(nextStatus()));
    passed_timer.setInterval(1000);
    connect(&passed_timer,SIGNAL(timeout()),this,SLOT(notifyRemaining()));
    passed_timer.start();

}

Status Pomodoro::status() const
{
    return m_status;
}

quint32 Pomodoro::pomodoroDuration() const
{
    return m_pomodoroDuration;
}

quint32 Pomodoro::shortBreakDuration() const
{
    return m_shortBreakDuration;
}

quint32 Pomodoro::longBreakDuration() const
{
    return m_longBreakDuration;
}

bool Pomodoro::pauseIsAllowed() const
{
    return m_pauseIsAllowed;
}

bool Pomodoro::autoContinue() const
{
    return m_autoContinue;
}

qint32 Pomodoro::passed() const
{
    qint32 _passed = passedTime();
    if (_passed != -1) _passed = std::floor(1. * _passed / 1000.);
    return _passed;
}

qint32 Pomodoro::remaining() const
{
    qint32 _remaining = remainingTime();
    if (_remaining != -1) _remaining = std::ceil(1. * _remaining / 1000.);
    return _remaining;
}



void Pomodoro::setStatus(Status status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(status);
}

void Pomodoro::setPomodoroDuration(quint32 pomodoroDuration)
{
    if (m_pomodoroDuration == pomodoroDuration)
        return;

    m_pomodoroDuration = pomodoroDuration;
    emit pomodoroDurationChanged(pomodoroDuration);
}

void Pomodoro::setShortBreakDuration(quint32 shortBreakDuration)
{
    if (m_shortBreakDuration == shortBreakDuration)
        return;

    m_shortBreakDuration = shortBreakDuration;
    emit shortBreakDurationChanged(shortBreakDuration);
}

void Pomodoro::setLongBreakDuration(quint32 longBreakDuration)
{
    if (m_longBreakDuration == longBreakDuration)
        return;

    m_longBreakDuration = longBreakDuration;
    emit longBreakDurationChanged(longBreakDuration);
}

void Pomodoro::setPauseIsAllowed(bool pauseIsAllowed)
{
    if (m_pauseIsAllowed == pauseIsAllowed)
        return;

    m_pauseIsAllowed = pauseIsAllowed;
    emit pauseIsAllowedChanged(pauseIsAllowed);
}

void Pomodoro::start(Status state)
{
    switch (state) {
    case Status::ACTIVE:
        timer.setInterval(pomodoroDuration());
        break;
    case Status::LONG_BREAK:
        timer.setInterval(longBreakDuration());
        break;
    case Status::SHORT_BREAK:
        timer.setInterval(shortBreakDuration());
        break;
    default:
        return;
    }
    setStatus(state);
    timer.start();
}

void Pomodoro::stop()
{
    timer.stop();
    setStatus(Status::STOPPED);
}

void Pomodoro::pause()
{
    if (!pauseIsAllowed()) return;
    if (status()==Status::PAUSED){
        timer.setInterval(pauseRemaining);
        timer.start();
        setStatus(Status::ACTIVE);
    }
    else {
        setStatus(Status::PAUSED);
        pauseRemaining = timer.remainingTime();
        timer.stop();
    }
}

void Pomodoro::setAutoContinue(bool autoContinue)
{
    if (m_autoContinue == autoContinue)
        return;

    m_autoContinue = autoContinue;
    emit autoContinueChanged(autoContinue);
}

qint32 Pomodoro::remainingTime() const
{
    return timer.remainingTime();
}

qint32 Pomodoro::passedTime() const
{
    switch (status()) {
    case Status::ACTIVE:
        return m_pomodoroDuration-timer.remainingTime();
    case Status::SHORT_BREAK:
        return m_shortBreakDuration-timer.remainingTime();
    case Status::LONG_BREAK:
        return m_longBreakDuration-timer.remainingTime();
    case Status::PAUSED:
        return m_pomodoroDuration-pauseRemaining;
    default:
        return -1;
    }
}

void Pomodoro::nextStatus()
{
    if (!autoContinue()){
        setStatus(Status::STOPPED);
        return;
    }
    switch (m_status) {
    case Status::ACTIVE:
        pomodorosAmount+=1;
        if (pomodorosAmount % 4 == 0){ //Long break
            timer.setInterval(longBreakDuration());
            setStatus(Status::LONG_BREAK);
            timer.start();
        }
        else{
            timer.setInterval(shortBreakDuration());
            timer.start();
            setStatus(Status::SHORT_BREAK);
            }
        break;
    case Status::LONG_BREAK:
    case Status::SHORT_BREAK:
        start();
        break;
    default:
        break;
    }

}

void Pomodoro::notifyRemaining()
{
    emit remainingChanged(remaining());
    emit passedChanged(passed());
}

