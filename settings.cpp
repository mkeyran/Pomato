#include "settings.h"

const char m_durationKey[] = "pomodoro/duration";
const char m_longBreakDurationKey[] = "pomodoro/long_break_duration";
const char m_shortBreakDurationKey[] = "pomodoro/short_break_duration";
const char m_autoContinueKey[] = "pomodoro/auto_continue";
const char m_allowPauseKey[] = "pomodoro/allow_pause";


Settings::Settings(std::weak_ptr<Pomodoro> pom, QObject *parent) : QObject(parent),
    settings("Keyran","Pomato")
{
    this->pom = pom;
    trytoget<quint32>(m_durationKey, m_duration, 1000*60*25);
    trytoget<quint32>(m_longBreakDurationKey, m_longBreakDuration, 1000*60*15);
    trytoget<quint32>(m_shortBreakDurationKey, m_shortBreakDuration, 1000*60*5);
    trytoget<bool>(m_autoContinueKey, m_autoContinue, true);
    trytoget<bool>(m_allowPauseKey, m_allowPause, true);
    std::shared_ptr<Pomodoro> pom_lock = pom.lock();
    if (pom_lock){
        pom_lock->setAutoContinue(m_autoContinue);
        pom_lock->setPomodoroDuration(m_duration);
        pom_lock->setLongBreakDuration(m_longBreakDuration);
        pom_lock->setShortBreakDuration(m_shortBreakDuration);
        pom_lock->setPauseIsAllowed(m_allowPause);
    }
}

void Settings::setDuration(quint32 duration)
{
    if (m_duration == duration)
        return;

    m_duration = duration;
    emit durationChanged(duration);
}

void Settings::setPlayPomodoroSound(bool playPomodoroSound)
{
    if (m_playPomodoroSound == playPomodoroSound)
        return;

    m_playPomodoroSound = playPomodoroSound;
    emit playPomodoroSoundChanged(playPomodoroSound);
}

void Settings::setPomodoroSound(QString pomodoroSound)
{
    if (m_pomodoroSound == pomodoroSound)
        return;

    m_pomodoroSound = pomodoroSound;
    emit pomodoroSoundChanged(pomodoroSound);
}


void Settings::setShortBreakDuration(quint32 shortBreakDuration)
{
    if (m_shortBreakDuration == shortBreakDuration)
        return;

    m_shortBreakDuration = shortBreakDuration;
    emit shortBreakDurationChanged(shortBreakDuration);
}

void Settings::setLongBreakDuration(quint32 longBreakDuration)
{
    if (m_longBreakDuration == longBreakDuration)
        return;

    m_longBreakDuration = longBreakDuration;
    emit longBreakDurationChanged(longBreakDuration);
}

void Settings::setAutoContinue(bool autoContinue)
{
    if (m_autoContinue == autoContinue)
        return;

    m_autoContinue = autoContinue;
    emit autoContinueChanged(autoContinue);
}

void Settings::setAllowPause(bool allowPause)
{
    if (m_allowPause == allowPause)
        return;

    m_allowPause = allowPause;
    emit allowPauseChanged(allowPause);
}

void Settings::setPlayTicks(bool playTicks)
{
    if (m_playTicks == playTicks)
        return;

    m_playTicks = playTicks;
    emit playTicksChanged(playTicks);
}

void Settings::setTicksSound(QString ticksSound)
{
    if (m_ticksSound == ticksSound)
        return;

    m_ticksSound = ticksSound;
    emit ticksSoundChanged(ticksSound);
}

void Settings::setPlayBreakSound(bool playBreakSound)
{
    if (m_playBreakSound == playBreakSound)
        return;

    m_playBreakSound = playBreakSound;
    emit playBreakSoundChanged(playBreakSound);
}

void Settings::setBreakSound(QString breakSound)
{
    if (m_breakSound == breakSound)
        return;

    m_breakSound = breakSound;
    emit breakSoundChanged(breakSound);
}

