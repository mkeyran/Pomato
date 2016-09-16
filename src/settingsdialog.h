#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <settings.h>
#include <memory>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog (std::weak_ptr<Settings> settings, QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void accept();
    void reject();
    void reset();
    void enableSounds();
    void chooseTickingSound();
    void chooseNewPomodoroSound();
    void chooseBreakSound();

private:
    std::weak_ptr<Settings> settings;
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
