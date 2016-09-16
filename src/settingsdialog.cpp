#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QTime>
#include <QFileDialog>
SettingsDialog::SettingsDialog (std::weak_ptr<Settings> settings, QWidget *parent) :
    QDialog (parent),
    settings (settings),
    ui (new Ui::SettingsDialog)
{
    ui->setupUi (this);
    connect (ui->newPomodoroSoundEnabled, SIGNAL (stateChanged (int)), this, SLOT (enableSounds()));
    connect (ui->breakSoundEnabled, SIGNAL (stateChanged (int)), this, SLOT (enableSounds()));
    connect (ui->tickingSoundEnabled, SIGNAL (stateChanged (int)), this, SLOT (enableSounds()));
    connect (ui->chooseBrakeSoundPB, SIGNAL (clicked (bool)), this, SLOT (chooseBreakSound()));
    connect (ui->chooseNewPomodoroSoundPB, SIGNAL (clicked (bool)), this, SLOT (chooseNewPomodoroSound()));
    connect (ui->chooseTickingSoundPB, SIGNAL (clicked (bool)), this, SLOT (chooseTickingSound()));
    connect (ui->pauseHotkeyReset, SIGNAL (clicked (bool)), ui->pauseHotkey, SLOT (clear()));
    connect (ui->startHotkeyReset, SIGNAL (clicked (bool)), ui->startHotkey, SLOT (clear()));
    connect (ui->stopHotkeyReset, SIGNAL (clicked (bool)), ui->stopHotkey, SLOT (clear()));
    reset();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::accept()
{
    std::shared_ptr<Settings> settings_lock = settings.lock();
    if (settings_lock) {
        settings_lock->setAllowPause (ui->allowPausesCB->isChecked());
        settings_lock->setAutoContinue (ui->autocycleCB->isChecked());
        settings_lock->setDuration (
            ui->pomodoroDurationTE->time().msecsSinceStartOfDay()
        );
        settings_lock->setShortBreakDuration (
            ui->shortBreakDurationTE->time().msecsSinceStartOfDay()
        );
        settings_lock->setLongBreakDuration (
            ui->longBreakDurationTE->time().msecsSinceStartOfDay()
        );
        settings_lock->setPlayBreakSound (ui->breakSoundEnabled->isChecked());
        settings_lock->setPlayticking (ui->tickingSoundEnabled->isChecked());
        settings_lock->setPlayPomodoroSound (ui->newPomodoroSoundEnabled->isChecked());
        settings_lock->settickingSound (QUrl (ui->tickingSoundLE->text()));
        settings_lock->setBreakSound (QUrl (ui->breakSoundLE->text()));
        settings_lock->setPomodoroSound (QUrl (ui->newPomodoroSoundLE->text()));
        settings_lock->setHotkeyPause (ui->pauseHotkey->keySequence().toString());
        settings_lock->setHotkeyStop (ui->stopHotkey->keySequence().toString());
        settings_lock->setHotkeyStart (ui->startHotkey->keySequence().toString());
    }
    QDialog::accept();
}

void SettingsDialog::reject()
{
    reset();
    QDialog::reject();
}

void SettingsDialog::reset()
{
    auto settings_lock = settings.lock();
    if (settings_lock) {
        ui->allowPausesCB->setChecked (settings_lock->allowPause());
        ui->autocycleCB->setChecked (settings_lock->autoContinue());
        ui->longBreakDurationTE->setTime (QTime::fromMSecsSinceStartOfDay (
                                              settings_lock->longBreakDuration()));
        ui->shortBreakDurationTE->setTime (QTime::fromMSecsSinceStartOfDay (
                                               settings_lock->shortBreakDuration()));
        ui->pomodoroDurationTE->setTime (QTime::fromMSecsSinceStartOfDay (
                                             settings_lock->duration()));
        ui->breakSoundEnabled->setChecked (settings_lock->playBreakSound());
        ui->tickingSoundEnabled->setChecked (settings_lock->playticking());
        ui->newPomodoroSoundEnabled->setChecked (settings_lock->playPomodoroSound());
        ui->newPomodoroSoundLE->setText (settings_lock->pomodoroSound().toString());
        ui->breakSoundLE->setText (settings_lock->breakSound().toString());
        ui->tickingSoundLE->setText (settings_lock->tickingSound().toString());
        ui->pauseHotkey->setKeySequence (QKeySequence (
                                             settings_lock->hotkeyPause(),
                                             QKeySequence::PortableText));
        ui->startHotkey->setKeySequence (QKeySequence (
                                             settings_lock->hotkeyStart(),
                                             QKeySequence::PortableText));
        ui->stopHotkey->setKeySequence (QKeySequence (
                                            settings_lock->hotkeyStop(),
                                            QKeySequence::PortableText));
    }
}

void SettingsDialog::enableSounds()
{
    ui->chooseBrakeSoundPB->setEnabled (ui->breakSoundEnabled->isChecked());
    ui->breakSoundLE->setEnabled (ui->breakSoundEnabled->isChecked());
    ui->chooseTickingSoundPB->setEnabled (ui->tickingSoundEnabled->isChecked());
    ui->tickingSoundLE->setEnabled (ui->tickingSoundEnabled->isChecked());
    ui->chooseNewPomodoroSoundPB->setEnabled (ui->newPomodoroSoundEnabled->isChecked());
    ui->newPomodoroSoundLE->setEnabled (ui->newPomodoroSoundEnabled->isChecked());
}

void SettingsDialog::chooseTickingSound()
{
    QUrl url = QFileDialog::getOpenFileUrl (this, "Choose sound file", ui->tickingSoundLE->text(), "Sound Files (*.mp3 *.wav *.ogg *.flac)");
    if (url.isValid()) {
        ui->tickingSoundLE->setText (url.toString());
    }
}

void SettingsDialog::chooseNewPomodoroSound()
{
    QUrl url = QFileDialog::getOpenFileUrl (this, "Choose sound file", ui->newPomodoroSoundLE->text(), "Sound Files (*.mp3 *.wav *.ogg *.flac)");
    if (url.isValid()) {
        ui->newPomodoroSoundLE->setText (url.toString());
    }
}

void SettingsDialog::chooseBreakSound()
{
    QUrl url = QFileDialog::getOpenFileUrl (this, "Choose sound file", ui->breakSoundLE->text(), "Sound Files (*.mp3 *.wav *.ogg *.flac)");
    if (url.isValid()) {
        ui->breakSoundLE->setText (url.toString());
    }
}
