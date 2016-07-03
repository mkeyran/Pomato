#ifndef SOUNDS_H
#define SOUNDS_H

#include <QObject>
#include <QMediaPlayer>
#include <settings.h>

class Sounds : public QObject
{
    Q_OBJECT
public:
    explicit Sounds(std::shared_ptr<Settings> settings, QObject *parent = 0);

signals:

public slots:
    void startTicking();
    void stopTickcing();
    void setTickingFileName(QUrl filename);
    void playNewPomodoro();
    void setNewPomodoroFileName(QUrl filename);
    void playBreak();
    void setBreakFileName(QUrl filename);
    void setTickingEnabled (bool enabled);
private slots:
    void repeatTicking(QMediaPlayer::MediaStatus status);

private:
    bool shouldTick = false;
    std::shared_ptr<Settings> settings;
    QMediaPlayer tickingPlayer;
    QMediaPlayer breakPlayer;
    QMediaPlayer newPomodoroPlayer;
};

#endif // SOUNDS_H
