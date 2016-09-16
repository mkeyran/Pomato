#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <memory>
#include <QVariant>
#include <QUrl>
#include <utils.h>
class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(quint32 shortBreakDuration READ shortBreakDuration WRITE setShortBreakDuration NOTIFY shortBreakDurationChanged)
    Q_PROPERTY(quint32 longBreakDuration READ longBreakDuration WRITE setLongBreakDuration NOTIFY longBreakDurationChanged)
    Q_PROPERTY(bool autoContinue READ autoContinue WRITE setAutoContinue NOTIFY autoContinueChanged)
    Q_PROPERTY(bool allowPause READ allowPause WRITE setAllowPause NOTIFY allowPauseChanged)
    Q_PROPERTY(bool playticking READ playticking WRITE setPlayticking NOTIFY playtickingChanged)
    Q_PROPERTY(QUrl tickingSound READ tickingSound WRITE settickingSound NOTIFY tickingSoundChanged)
    Q_PROPERTY(bool playBreakSound READ playBreakSound WRITE setPlayBreakSound NOTIFY playBreakSoundChanged)
    Q_PROPERTY(QUrl breakSound READ breakSound WRITE setBreakSound NOTIFY breakSoundChanged)
    Q_PROPERTY(bool playPomodoroSound READ playPomodoroSound WRITE setPlayPomodoroSound NOTIFY playPomodoroSoundChanged)
    Q_PROPERTY(QUrl pomodoroSound READ pomodoroSound WRITE setPomodoroSound NOTIFY pomodoroSoundChanged)
public:
    explicit Settings(QObject *parent = 0);

    quint32 duration() const
    {
        return m_duration;
    }

    quint32 shortBreakDuration() const
    {
        return m_shortBreakDuration;
    }

    quint32 longBreakDuration() const
    {
        return m_longBreakDuration;
    }

    bool autoContinue() const
    {
        return m_autoContinue;
    }

    bool allowPause() const
    {
        return m_allowPause;
    }

    bool playticking() const
    {
        return m_playticking;
    }

    QUrl tickingSound() const
    {
        return m_tickingSound;
    }

    bool playBreakSound() const
    {
        return m_playBreakSound;
    }

    QUrl breakSound() const
    {
        return m_breakSound;
    }

    bool playPomodoroSound() const
    {
        return m_playPomodoroSound;
    }

    QUrl pomodoroSound() const
    {
        return m_pomodoroSound;
    }

signals:

    void durationChanged(quint32 duration);

    void shortBreakDurationChanged(quint32 shortBreakDuration);

    void longBreakDurationChanged(quint32 longBreakDuration);

    void autoContinueChanged(bool autoContinue);

    void allowPauseChanged(bool allowPause);

    void playtickingChanged(bool playticking);

    void tickingSoundChanged(QUrl tickingSound);

    void playBreakSoundChanged(bool playBreakSound);

    void breakSoundChanged(QUrl breakSound);

    void playPomodoroSoundChanged(bool playPomodoroSound);

    void pomodoroSoundChanged(QUrl pomodoroSound);

public slots:

void setDuration(quint32 duration);

void setShortBreakDuration(quint32 shortBreakDuration);

void setLongBreakDuration(quint32 longBreakDuration);

void setAutoContinue(bool autoContinue);

void setAllowPause(bool allowPause);

void setPlayticking(bool playticking);

void settickingSound(QUrl tickingSound);

void setPlayBreakSound(bool playBreakSound);

void setBreakSound(QUrl breakSound);

void setPlayPomodoroSound(bool playPomodoroSound);

void setPomodoroSound(QUrl pomodoroSound);

void load();

private:
quint32 m_duration;
quint32 m_shortBreakDuration;
quint32 m_longBreakDuration;
bool m_autoContinue;
bool m_allowPause;
bool m_playticking;
QUrl m_tickingSound;
bool m_playBreakSound;
QUrl m_breakSound;
bool m_playPomodoroSound;
QUrl m_pomodoroSound;

template <class T>
void trytoget(const char *key, void (Settings::*var_setter)(T), const T& def){
    QVariant val = settings.value(key);
    if (!val.isNull() && val.canConvert<T>()){
        (this->*var_setter)(val.value<T>());
    }
    else {
        (this->*var_setter)(def);
        settings.setValue(key,def);
    }
}

QSettings settings;
};


#endif // SETTINGS_H
