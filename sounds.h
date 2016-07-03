#ifndef SOUNDS_H
#define SOUNDS_H

#include <QObject>
#include <QMediaPlayer>
class Sounds : public QObject
{
    Q_OBJECT
public:
    explicit Sounds(QObject *parent = 0);

signals:

public slots:
    void startTicking();
    void stopTickcing();
    void setTickingFileName(QUrl filename);
    void playNewPomodoro();
    void setNewPomodoroFileName(QUrl filename);
    void playBreak();
    void setBreakFileName(QUrl filename);
    void setTickingEnabled(bool enabled);
    void setNewPomodoroEnabled(bool enabled);
    void setBreakEnabled(bool enabled);

private slots:
    void repeatTicking(QMediaPlayer::MediaStatus status);


private:
    bool tickingEnabled = false;
    bool breakEnabled = false;
    bool newPomodoroEnabled = false;
    bool shouldTick = false;
    QMediaPlayer tickingPlayer;
    QMediaPlayer breakPlayer;
    QMediaPlayer newPomodoroPlayer;
};

#endif // SOUNDS_H
