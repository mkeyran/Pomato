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
const char m_hotkeyStartKey[] = "hotkeys/start";
const char m_hotkeyStopKey[] = "hotkeys/stop";
const char m_hotkeyPauseKey[] = "hotkeys/pause";


Settings::Settings (QObject *parent) : QObject (parent),
    settings ("Keyran", "Pomato")
{
}

void Settings::setDuration (quint32 duration)
{
    if (m_duration == duration)
        return;
    m_duration = duration;
    settings.setValue (m_durationKey, duration);
    emit durationChanged (duration);
}

void Settings::setPlayPomodoroSound (bool playPomodoroSound)
{
    if (m_playPomodoroSound == playPomodoroSound)
        return;
    m_playPomodoroSound = playPomodoroSound;
    settings.setValue (m_pomodoroSoundEnabledKey, m_playPomodoroSound);
    emit playPomodoroSoundChanged (playPomodoroSound);
}

void Settings::setPomodoroSound (QUrl pomodoroSound)
{
    if (m_pomodoroSound == pomodoroSound)
        return;
    m_pomodoroSound = pomodoroSound;
    settings.setValue (m_pomodoroSoundKey, m_pomodoroSound);
    emit pomodoroSoundChanged (pomodoroSound);
}

void Settings::load()
{
    trytoget<quint32> (m_durationKey, &Settings::setDuration, (quint32)1000 * 60 * 25);
    trytoget<quint32> (m_longBreakDurationKey, &Settings::setLongBreakDuration, 1000 * 60 * 15);
    trytoget<quint32> (m_shortBreakDurationKey, &Settings::setShortBreakDuration, 1000 * 60 * 5);
    trytoget<bool> (m_autoContinueKey, &Settings::setAutoContinue, true);
    trytoget<bool> (m_allowPauseKey, &Settings::setAllowPause, true);
    trytoget<QUrl> (m_pomodoroSoundKey, &Settings::setPomodoroSound, QUrl (""));
    trytoget<QUrl> (m_breakSoundKey, &Settings::setBreakSound, QUrl (""));
    trytoget<QUrl> (m_tickingSoundKey, &Settings::settickingSound, QUrl (""));
    trytoget<bool> (m_tickingSoundEnabledKey, &Settings::setPlayticking, false);
    trytoget<bool> (m_pomodoroSoundEnabledKey, &Settings::setPlayPomodoroSound, false);
    trytoget<bool> (m_breakSoundEnabledKey, &Settings::setPlayBreakSound, false);
    trytoget<QString> (m_hotkeyStartKey, &Settings::setHotkeyStart, "");
    trytoget<QString> (m_hotkeyStopKey, &Settings::setHotkeyStop, "");
    trytoget<QString> (m_hotkeyPauseKey, &Settings::setHotkeyPause, "");
}

void Settings::setHotkeyStart (QString hotkeyStart)
{
    if (m_hotkeyStart == hotkeyStart)
        return;
    m_hotkeyStart = hotkeyStart;
    settings.setValue (m_hotkeyStartKey, hotkeyStart);
    emit hotkeyStartChanged (hotkeyStart);
}

void Settings::setHotkeyPause (QString hotkeyPause)
{
    if (m_hotkeyPause == hotkeyPause)
        return;
    m_hotkeyPause = hotkeyPause;
    settings.setValue (m_hotkeyPauseKey, hotkeyPause);
    emit hotkeyPauseChanged (hotkeyPause);
}

void Settings::setHotkeyStop (QString hotkeyStop)
{
    if (m_hotkeyStop == hotkeyStop)
        return;
    m_hotkeyStop = hotkeyStop;
    settings.setValue (m_hotkeyStopKey, hotkeyStop);
    emit hotkeyStopChanged (hotkeyStop);
}


void Settings::setShortBreakDuration (quint32 shortBreakDuration)
{
    if (m_shortBreakDuration == shortBreakDuration)
        return;
    m_shortBreakDuration = shortBreakDuration;
    settings.setValue (m_shortBreakDurationKey, shortBreakDuration);
    emit shortBreakDurationChanged (shortBreakDuration);
}

void Settings::setLongBreakDuration (quint32 longBreakDuration)
{
    if (m_longBreakDuration == longBreakDuration)
        return;
    m_longBreakDuration = longBreakDuration;
    settings.setValue (m_longBreakDurationKey, longBreakDuration);
    emit longBreakDurationChanged (longBreakDuration);
}

void Settings::setAutoContinue (bool autoContinue)
{
    if (m_autoContinue == autoContinue)
        return;
    m_autoContinue = autoContinue;
    settings.setValue (m_autoContinueKey, autoContinue);
    emit autoContinueChanged (autoContinue);
}

void Settings::setAllowPause (bool allowPause)
{
    if (m_allowPause == allowPause)
        return;
    m_allowPause = allowPause;
    settings.setValue (m_allowPauseKey, allowPause);
    emit allowPauseChanged (allowPause);
}

void Settings::setPlayticking (bool playticking)
{
    if (m_playticking == playticking)
        return;
    m_playticking = playticking;
    settings.setValue (m_tickingSoundEnabledKey, m_playticking);
    emit playtickingChanged (playticking);
}

void Settings::settickingSound (QUrl tickingSound)
{
    if (m_tickingSound == tickingSound)
        return;
    m_tickingSound = tickingSound;
    settings.setValue (m_tickingSoundKey, m_tickingSound);
    emit tickingSoundChanged (tickingSound);
}

void Settings::setPlayBreakSound (bool playBreakSound)
{
    if (m_playBreakSound == playBreakSound)
        return;
    m_playBreakSound = playBreakSound;
    settings.setValue (m_breakSoundEnabledKey, m_playBreakSound);
    emit playBreakSoundChanged (playBreakSound);
}

void Settings::setBreakSound (QUrl breakSound)
{
    if (m_breakSound == breakSound)
        return;
    m_breakSound = breakSound;
    settings.setValue (m_breakSoundKey, m_breakSound);
    emit breakSoundChanged (breakSound);
}
