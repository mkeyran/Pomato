#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <pomodoro.h>
#include <memory>
#include <QVariant>
class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32 duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(quint32 shortBreakDuration READ shortBreakDuration WRITE setShortBreakDuration NOTIFY shortBreakDurationChanged)
    Q_PROPERTY(quint32 longBreakDuration READ longBreakDuration WRITE setLongBreakDuration NOTIFY longBreakDurationChanged)
    Q_PROPERTY(bool autoContinue READ autoContinue WRITE setAutoContinue NOTIFY autoContinueChanged)
    Q_PROPERTY(bool allowPause READ allowPause WRITE setAllowPause NOTIFY allowPauseChanged)
    Q_PROPERTY(bool playTicks READ playTicks WRITE setPlayTicks NOTIFY playTicksChanged)
    Q_PROPERTY(QString ticksSound READ ticksSound WRITE setTicksSound NOTIFY ticksSoundChanged)
    Q_PROPERTY(bool playBreakSound READ playBreakSound WRITE setPlayBreakSound NOTIFY playBreakSoundChanged)
    Q_PROPERTY(QString breakSound READ breakSound WRITE setBreakSound NOTIFY breakSoundChanged)
    Q_PROPERTY(bool playPomodoroSound READ playPomodoroSound WRITE setPlayPomodoroSound NOTIFY playPomodoroSoundChanged)
    Q_PROPERTY(QString pomodoroSound READ pomodoroSound WRITE setPomodoroSound NOTIFY pomodoroSoundChanged)
public:
    explicit Settings(std::weak_ptr<Pomodoro> pom, QObject *parent = 0);

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

    bool playTicks() const
    {
        return m_playTicks;
    }

    QString ticksSound() const
    {
        return m_ticksSound;
    }

    bool playBreakSound() const
    {
        return m_playBreakSound;
    }

    QString breakSound() const
    {
        return m_breakSound;
    }

    bool playPomodoroSound() const
    {
        return m_playPomodoroSound;
    }

    QString pomodoroSound() const
    {
        return m_pomodoroSound;
    }

signals:

    void durationChanged(quint32 duration);

    void shortBreakDurationChanged(quint32 shortBreakDuration);

    void longBreakDurationChanged(quint32 longBreakDuration);

    void autoContinueChanged(bool autoContinue);

    void allowPauseChanged(bool allowPause);

    void playTicksChanged(bool playTicks);

    void ticksSoundChanged(QString ticksSound);

    void playBreakSoundChanged(bool playBreakSound);

    void breakSoundChanged(QString breakSound);

    void playPomodoroSoundChanged(bool playPomodoroSound);

    void pomodoroSoundChanged(QString pomodoroSound);

public slots:

void setDuration(quint32 duration);

void setShortBreakDuration(quint32 shortBreakDuration);

void setLongBreakDuration(quint32 longBreakDuration);

void setAutoContinue(bool autoContinue);

void setAllowPause(bool allowPause);

void setPlayTicks(bool playTicks);

void setTicksSound(QString ticksSound);

void setPlayBreakSound(bool playBreakSound);

void setBreakSound(QString breakSound);

void setPlayPomodoroSound(bool playPomodoroSound);

void setPomodoroSound(QString pomodoroSound);

private:
quint32 m_duration;
quint32 m_shortBreakDuration;
quint32 m_longBreakDuration;
bool m_autoContinue;
bool m_allowPause;
bool m_playTicks;
QString m_ticksSound;
bool m_playBreakSound;
QString m_breakSound;
bool m_playPomodoroSound;
QString m_pomodoroSound;

template <class T>
void trytoget(const char *key, T& var, const T& def){
    QVariant val = settings.value(key);
    if (!val.isNull() && val.canConvert<T>()){
        var = val.value<T>();
    }
    else {
        var = def;
        settings.setValue(key,def);
    }
}


std::weak_ptr<Pomodoro> pom;
QSettings settings;
};

#endif // SETTINGS_H
