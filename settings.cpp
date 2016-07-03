#include "settings.h"
#include "utils.h"

const char m_durationKey[] = "pomodoro/duration";
const char m_longBreakDurationKey[] = "pomodoro/long_break_duration";
const char m_shortBreakDurationKey[] = "pomodoro/short_break_duration";
const char m_autoContinueKey[] = "pomodoro/auto_continue";
const char m_allowPauseKey[] = "pomodoro/allow_pause";
const char m_pomodoroSoundKey[] = "sounds/new_pomodoro";
const char m_breakSoundKey[] = "sounds/break";
const char m_tickingSoundKey[] = "sounds/ticking";
const char m_pomodoroSoundEnabledKey[] = "sounds/new_pomodoro_enabled";
const char m_breakSoundEnabledKey[] = "sounds/break_enabled";
const char m_tickingSoundEnabledKey[] = "sounds/ticking_enabled";

Settings::Settings(std::weak_ptr<Pomodoro> pom, std::weak_ptr<Sounds> sounds, QObject *parent) : QObject(parent),
    settings("Keyran","Pomato")
{
    this->pom = pom;
    this->sounds = sounds;
    trytoget<quint32>(m_durationKey, m_duration, 1000*60*25);
    trytoget<quint32>(m_longBreakDurationKey, m_longBreakDuration, 1000*60*15);
    trytoget<quint32>(m_shortBreakDurationKey, m_shortBreakDuration, 1000*60*5);
    trytoget<bool>(m_autoContinueKey, m_autoContinue, true);
    trytoget<bool>(m_allowPauseKey, m_allowPause, true);
    trytoget<QUrl>(m_pomodoroSoundKey, m_pomodoroSound, QUrl(""));
    trytoget<QUrl>(m_breakSoundKey, m_breakSound, QUrl(""));
    trytoget<QUrl>(m_tickingSoundKey, m_tickingSound, QUrl(""));
    trytoget<bool>(m_tickingSoundEnabledKey, m_playticking, false);
    trytoget<bool>(m_pomodoroSoundEnabledKey, m_playPomodoroSound, false);
    trytoget<bool>(m_breakSoundEnabledKey, m_playBreakSound, false);
    with_weak_ptr(pom,[this](auto l){
        l->setAutoContinue(m_autoContinue);
        l->setPomodoroDuration(m_duration);
        l->setLongBreakDuration(m_longBreakDuration);
        l->setShortBreakDuration(m_shortBreakDuration);
        l->setPauseIsAllowed(m_allowPause);
    });
    with_weak_ptr(sounds,[this](std::shared_ptr<Sounds> s){
       s->setBreakEnabled(m_playBreakSound);
       s->setBreakFileName(m_breakSound);
       s->setNewPomodoroEnabled(m_playPomodoroSound);
       s->setNewPomodoroFileName(m_pomodoroSound);
       s->setTickingEnabled(m_playticking);
       s->setTickingFileName(m_tickingSound);
    });
}

void Settings::setDuration(quint32 duration)
{
    if (m_duration == duration)
        return;

    m_duration = duration;
    settings.setValue(m_durationKey, duration);
    with_weak_ptr(pom,[this](auto pom_lock){
        pom_lock->setPomodoroDuration(m_duration);
    });
    emit durationChanged(duration);
}

void Settings::setPlayPomodoroSound(bool playPomodoroSound)
{
    if (m_playPomodoroSound == playPomodoroSound)
        return;

    m_playPomodoroSound = playPomodoroSound;
    settings.setValue(m_pomodoroSoundEnabledKey, m_playPomodoroSound);
    with_weak_ptr(sounds,[this](auto s){
       s->setNewPomodoroEnabled(m_playPomodoroSound);
    });
    emit playPomodoroSoundChanged(playPomodoroSound);
}

void Settings::setPomodoroSound(QUrl pomodoroSound)
{
    if (m_pomodoroSound == pomodoroSound)
        return;

    m_pomodoroSound = pomodoroSound;
    settings.setValue(m_pomodoroSoundKey, m_pomodoroSound);
    with_weak_ptr(sounds,[this](auto s){
       s->setNewPomodoroFileName(m_pomodoroSound);
    });
    emit pomodoroSoundChanged(pomodoroSound);
}


void Settings::setShortBreakDuration(quint32 shortBreakDuration)
{
    if (m_shortBreakDuration == shortBreakDuration)
        return;

    m_shortBreakDuration = shortBreakDuration;
    settings.setValue(m_shortBreakDurationKey, shortBreakDuration);
    with_weak_ptr(pom,[this](auto pom_lock){
        pom_lock->setShortBreakDuration(m_shortBreakDuration);
    });
    emit shortBreakDurationChanged(shortBreakDuration);
}

void Settings::setLongBreakDuration(quint32 longBreakDuration)
{
    if (m_longBreakDuration == longBreakDuration)
        return;

    m_longBreakDuration = longBreakDuration;
    settings.setValue(m_longBreakDurationKey, longBreakDuration);
    with_weak_ptr(pom,[this](auto pom_lock){
        pom_lock->setLongBreakDuration(m_longBreakDuration);
    });
    emit longBreakDurationChanged(longBreakDuration);
}

void Settings::setAutoContinue(bool autoContinue)
{
    if (m_autoContinue == autoContinue)
        return;

    m_autoContinue = autoContinue;
    settings.setValue(m_autoContinueKey, autoContinue);
    with_weak_ptr(pom,[this](auto pom_lock){
        pom_lock->setAutoContinue(m_autoContinue);
    });
    emit autoContinueChanged(autoContinue);
}

void Settings::setAllowPause(bool allowPause)
{
    if (m_allowPause == allowPause)
        return;

    m_allowPause = allowPause;
    settings.setValue(m_allowPauseKey, allowPause);
    with_weak_ptr(pom,[this](auto pom_lock){
        pom_lock->setPauseIsAllowed(m_allowPause);
    });
    emit allowPauseChanged(allowPause);
}

void Settings::setPlayticking(bool playticking)
{
    if (m_playticking == playticking)
        return;

    m_playticking = playticking;
    settings.setValue(m_tickingSoundEnabledKey, m_playticking);
    with_weak_ptr(sounds,[this](auto s){
       s->setTickingEnabled(m_playticking);
    });
    emit playtickingChanged(playticking);
}

void Settings::settickingSound(QUrl tickingSound)
{
    if (m_tickingSound == tickingSound)
        return;

    m_tickingSound = tickingSound;
    settings.setValue(m_tickingSoundKey, m_tickingSound);
    with_weak_ptr(sounds,[this](auto s){
       s->setTickingFileName(m_tickingSound);
    });
    emit tickingSoundChanged(tickingSound);
}

void Settings::setPlayBreakSound(bool playBreakSound)
{
    if (m_playBreakSound == playBreakSound)
        return;

    m_playBreakSound = playBreakSound;
    settings.setValue(m_breakSoundEnabledKey,m_playBreakSound);
    with_weak_ptr(sounds,[this](auto s){
       s->setBreakEnabled(m_playBreakSound);
    });
    emit playBreakSoundChanged(playBreakSound);
}

void Settings::setBreakSound(QUrl breakSound)
{
    if (m_breakSound == breakSound)
        return;

    m_breakSound = breakSound;
    settings.setValue(m_breakSoundKey, m_breakSound);
    with_weak_ptr(sounds,[this](auto s){
       s->setBreakFileName(m_breakSound);
    });
    emit breakSoundChanged(breakSound);
}

