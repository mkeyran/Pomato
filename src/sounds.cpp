#include "sounds.h"

Sounds::Sounds(std::shared_ptr<Settings> settings, QObject *parent) : QObject(parent),
    settings(settings)
{
    connect(&tickingPlayer,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this,SLOT(repeatTicking(QMediaPlayer::MediaStatus)));
    connect(settings.get(), SIGNAL(playtickingChanged(bool)),this,SLOT(setTickingEnabled(bool)));
    connect(settings.get(), SIGNAL(breakSoundChanged(QUrl)),this,SLOT(setBreakFileName(QUrl)));
    connect(settings.get(), SIGNAL(tickingSoundChanged(QUrl)),this, SLOT(setTickingFileName(QUrl)));
    connect(settings.get(), SIGNAL(pomodoroSoundChanged(QUrl)), this, SLOT(setNewPomodoroFileName(QUrl)));
}

void Sounds::startTicking()
{
    shouldTick = true;
    if (settings->playticking() && tickingPlayer.isAudioAvailable()){
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
    if (settings->playPomodoroSound() && newPomodoroPlayer.isAudioAvailable())
        newPomodoroPlayer.play();
}

void Sounds::setNewPomodoroFileName(QUrl filename)
{
    newPomodoroPlayer.setMedia(QMediaContent(filename));
}

void Sounds::playBreak()
{
    if (settings->playBreakSound() && breakPlayer.isAudioAvailable()){
        breakPlayer.play();
    }
}

void Sounds::setBreakFileName(QUrl filename)
{
    breakPlayer.setMedia(QMediaContent(filename));
}

void Sounds::setTickingEnabled(bool enabled)
{
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
void Sounds::repeatTicking(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia){
        startTicking();
    }
}
