#include "pomodoro.h"
#include <cmath>
#include <QDebug>
#include <QTime>

Pomodoro::Pomodoro (std::shared_ptr<Settings> settings, QObject *parent)
    : QObject (parent),
      m_state (State::STOPPED),
      pomodorosAmount (0),
      m_prevState (State::STOPPED),
      settings (settings)
{
    //    timer.setTimerType(Qt::VeryCoarseTimer);
    timer.setSingleShot (true);
    connect (&timer, SIGNAL (timeout()), this, SLOT (nextState()));
    passed_timer.setTimerType (Qt::PreciseTimer);
    passed_timer.setInterval (500);
    connect (&passed_timer, SIGNAL (timeout()), this, SLOT (notifyRemaining()));
    passed_timer.start();
}

State Pomodoro::state() const
{
    return m_state;
}

qint32 Pomodoro::passed() const
{
    qint32 _passed = passedTime();
    if (_passed != -1) _passed = std::ceil (1. * _passed / 1000.);
    return _passed;
}

qint32 Pomodoro::remaining() const
{
    qint32 _remaining = remainingTime();
    if (_remaining != -1) _remaining = std::floor (1. * _remaining / 1000.);
    return _remaining;
}

State Pomodoro::prevState() const
{
    return m_prevState;
}



void Pomodoro::setState (State state)
{
    if (m_state == state)
        return;
    setPrevState (m_state);
    m_state = state;
    notifyRemaining();
    emit stateChanged (state);
}


void Pomodoro::start (State state)
{
    switch (state) {
        case State::ACTIVE:
            timer.setInterval (settings->duration());
            break;
        case State::LONG_BREAK:
            timer.setInterval (settings->longBreakDuration());
            break;
        case State::SHORT_BREAK:
            timer.setInterval (settings->shortBreakDuration());
            break;
        default:
            return;
    }
    timer.start();
    setState (state);
}

void Pomodoro::stop()
{
    timer.stop();
    pomodorosAmount = 0;
    setState (State::STOPPED);
}

void Pomodoro::pause()
{
    if (!settings->allowPause()) return;
    if (state() == State::STOPPED
            || state() == State::LONG_BREAK
            || state() == State::SHORT_BREAK) return;
    if (state() == State::PAUSED) {
        timer.setInterval (pauseRemaining);
        timer.start();
        setState (State::ACTIVE);
    } else {
        pauseRemaining = timer.remainingTime();
        timer.stop();
        setState (State::PAUSED);
    }
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
            return settings->duration() - timer.remainingTime();
        case State::SHORT_BREAK:
            return settings->shortBreakDuration() - timer.remainingTime();
        case State::LONG_BREAK:
            return settings->longBreakDuration() - timer.remainingTime();
        case State::PAUSED:
            return settings->duration() - pauseRemaining;
        default:
            return -1;
    }
}

void Pomodoro::nextState()
{
    if (!settings->autoContinue()) {
        setState (State::STOPPED);
        return;
    }
    switch (m_state) {
        case State::ACTIVE:
            pomodorosAmount += 1;
            if (pomodorosAmount % 4 == 0) { //Long break
                timer.setInterval (settings->longBreakDuration());
                timer.start();
                setState (State::LONG_BREAK);
            } else {
                timer.setInterval (settings->shortBreakDuration());
                timer.start();
                setState (State::SHORT_BREAK);
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
    emit remainingChanged (remaining());
    emit passedChanged (passed());
}

void Pomodoro::setPrevState (State prevState)
{
    if (m_prevState == prevState)
        return;
    m_prevState = prevState;
}
