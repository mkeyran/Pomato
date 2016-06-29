#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QTime>
SettingsDialog::SettingsDialog(std::weak_ptr<Settings> settings, QWidget *parent) :
    QDialog(parent),
    settings(settings),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    reset();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::accept()
{
    std::shared_ptr<Settings> settings_lock = settings.lock();
    if (settings_lock){
        settings_lock->setAllowPause(ui->allowPausesCB->isChecked());
        settings_lock->setAutoContinue(ui->autocycleCB->isChecked());
        settings_lock->setDuration(
                    ui->pomodoroDurationTE->time().msecsSinceStartOfDay()
                    );
        settings_lock->setShortBreakDuration(
                    ui->shortBreakDurationTE->time().msecsSinceStartOfDay()
                    );
        settings_lock->setLongBreakDuration(
                    ui->longBreakDurationTE->time().msecsSinceStartOfDay()
                    );
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
    if (settings_lock){
        ui->allowPausesCB->setChecked(settings_lock->allowPause());
        ui->autocycleCB->setChecked(settings_lock->autoContinue());
        ui->longBreakDurationTE->setTime(QTime::fromMSecsSinceStartOfDay(
                                             settings_lock->longBreakDuration()));
        ui->shortBreakDurationTE->setTime(QTime::fromMSecsSinceStartOfDay(
                                             settings_lock->shortBreakDuration()));
        ui->pomodoroDurationTE->setTime(QTime::fromMSecsSinceStartOfDay(
                                             settings_lock->duration()));
    }
}
