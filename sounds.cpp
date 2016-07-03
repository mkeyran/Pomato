#include "sounds.h"

Sounds::Sounds(QObject *parent) : QObject(parent)
{
    connect(&tickingPlayer,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this,SLOT(repeatTicking(QMediaPlayer::MediaStatus)));
}

void Sounds::startTicking()
{
    shouldTick = true;
    if (tickingEnabled && tickingPlayer.isAudioAvailable()){
        tickingPlayer.play();
    }
}

void Sounds::stopTickcing()
{
    shouldTick = false;
    tickingPlayer.stop();
}

void Sounds::setTickingFileName(QUrl filename)
{
    tickingPlayer.setMedia(QMediaContent(filename));
}

void Sounds::playNewPomodoro()
{
    if (newPomodoroEnabled && newPomodoroPlayer.isAudioAvailable())
        newPomodoroPlayer.play();
}

void Sounds::setNewPomodoroFileName(QUrl filename)
{
    newPomodoroPlayer.setMedia(QMediaContent(filename));
}

void Sounds::playBreak()
{
    if (breakEnabled && breakPlayer.isAudioAvailable()){
        breakPlayer.play();
    }
}

void Sounds::setBreakFileName(QUrl filename)
{
    breakPlayer.setMedia(QMediaContent(filename));
}

void Sounds::setTickingEnabled(bool enabled)
{
    tickingEnabled = enabled;
    if (shouldTick && enabled){
        if (tickingPlayer.state() !=  QMediaPlayer::PlayingState) {
             tickingPlayer.play();
        }
    }
    else {
        if (tickingPlayer.state() == QMediaPlayer::PlayingState){
             tickingPlayer.stop();
        }
    }
}

void Sounds::setNewPomodoroEnabled(bool enabled)
{
    newPomodoroEnabled = enabled;
}

void Sounds::setBreakEnabled(bool enabled)
{
    breakEnabled = enabled;
}

void Sounds::repeatTicking(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia){
        startTicking();
    }
}
