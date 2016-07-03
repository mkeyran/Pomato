#include "pomodoro.h"
#include <cmath>
#include <QDebug>
#include <QTime>

Pomodoro::Pomodoro(QObject *parent) : Pomodoro(1000*60*25,1000*60*5,1000*60*15,parent)
{
}

Pomodoro::Pomodoro(quint32 pomodoroDuration, quint32 shortBreakDuration, quint32 longBreakDuration, QObject *parent)
    : QObject(parent),
      m_state(State::STOPPED),
      m_pomodoroDuration(pomodoroDuration),
      m_shortBreakDuration(shortBreakDuration),
      m_longBreakDuration(longBreakDuration),
      m_pauseIsAllowed(true),
      m_autoContinue(true),
      pomodorosAmount(0),
      m_prevState(State::STOPPED)
{
//    timer.setTimerType(Qt::VeryCoarseTimer);
    timer.setSingleShot(true);
    connect(&timer,SIGNAL(timeout()),this,SLOT(nextState()));
    passed_timer.setTimerType(Qt::PreciseTimer);
    passed_timer.setInterval(500);
    connect(&passed_timer,SIGNAL(timeout()),this,SLOT(notifyRemaining()));
    passed_timer.start();

}

State Pomodoro::state() const
{
    return m_state;
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
    if (_passed != -1) _passed = std::ceil(1. * _passed / 1000.);
    return _passed;
}

qint32 Pomodoro::remaining() const
{
    qint32 _remaining = remainingTime();
    if (_remaining != -1) _remaining = std::floor(1. * _remaining / 1000.);
    return _remaining;
}

State Pomodoro::prevState() const
{
    return m_prevState;
}



void Pomodoro::setState(State state)
{
    if (m_state == state)
        return;
    setPrevState(m_state);
    m_state = state;
    notifyRemaining();
    emit stateChanged(state);
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

void Pomodoro::start(State state)
{
    switch (state) {
    case State::ACTIVE:
        timer.setInterval(pomodoroDuration());
        break;
    case State::LONG_BREAK:
        timer.setInterval(longBreakDuration());
        break;
    case State::SHORT_BREAK:
        timer.setInterval(shortBreakDuration());
        break;
    default:
        return;
    }
    timer.start();
    setState(state);
}

void Pomodoro::stop()
{
    timer.stop();
    pomodorosAmount = 0;
    setState(State::STOPPED);
}

void Pomodoro::pause()
{
    if (!pauseIsAllowed()) return;
    if (state()==State::PAUSED){
        timer.setInterval(pauseRemaining);
        timer.start();
        setState(State::ACTIVE);
    }
    else {
        pauseRemaining = timer.remainingTime();
        timer.stop();
        setState(State::PAUSED);
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
    switch (state()) {
    case State::ACTIVE:
    case State::SHORT_BREAK:
    case State::LONG_BREAK:
        return timer.remainingTime();
    case State::PAUSED:
        return pauseRemaining;
    default:
        return -1;
    }
}

qint32 Pomodoro::passedTime() const
{
    switch (state()) {
    case State::ACTIVE:
        return m_pomodoroDuration-timer.remainingTime();
    case State::SHORT_BREAK:
        return m_shortBreakDuration-timer.remainingTime();
    case State::LONG_BREAK:
        return m_longBreakDuration-timer.remainingTime();
    case State::PAUSED:
        return m_pomodoroDuration-pauseRemaining;
    default:
        return -1;
    }
}

void Pomodoro::nextState()
{
    if (!autoContinue()){
        setState(State::STOPPED);
        return;
    }
    switch (m_state) {
    case State::ACTIVE:
        pomodorosAmount+=1;
        if (pomodorosAmount % 4 == 0){ //Long break
            timer.setInterval(longBreakDuration());
            timer.start();
            setState(State::LONG_BREAK);
        }
        else{
            timer.setInterval(shortBreakDuration());
            timer.start();
            setState(State::SHORT_BREAK);
            }
        break;
    case State::LONG_BREAK:
    case State::SHORT_BREAK:
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

void Pomodoro::setPrevState(State prevState)
{
    if (m_prevState == prevState)
        return;

    m_prevState = prevState;
}

