#include "trayicon.h"
#include <QPainter>
#include <cmath>
#include <QApplication>
#include <mainwindow.h>
#include <QDebug>
TrayIcon::TrayIcon (QObject *parent) : QObject (parent)
{
    settings = std::make_shared<Settings> (this);
    sounds = std::make_shared<Sounds> (settings, this);
    pom = std::make_shared<Pomodoro> (settings, this);
    mainwindow = new MainWindow (pom, settings);
    settings->load();
    // Icon setting
    pixmap.load (":/icons/tomato.svg");
    icon.addPixmap (pixmap.scaled (QSize (32, 32), Qt::KeepAspectRatio));
    tray.setIcon (icon);
    // Menu setting
    menu.addAction (tr ("Start"), this->pom.get(), SLOT (start()));
    menu.addAction (tr ("Pause"), this->pom.get(), SLOT (pause()));
    menu.actions()[1]->setVisible (false);
    menu.addAction (tr ("Stop"), this->pom.get(), SLOT (stop()));
    menu.actions()[2]->setVisible (false);
    menu.addSeparator();
    menu.addAction (tr ("Settings"), this, SLOT (showSettingsDialog()));
    menu.addAction (tr ("Exit"), this, SLOT (exit()));
    tray.setContextMenu (&menu);
    // Hotkeys setting
    setHotkeys();
    // Signals connection
    connect (&tray, SIGNAL (activated (QSystemTrayIcon::ActivationReason)),
             this, SLOT (trayActivated (QSystemTrayIcon::ActivationReason)));
    connect (mainwindow, SIGNAL (showSettings()), this, SLOT (showSettingsDialog()));
    connect (pom.get(), SIGNAL (remainingChanged (qint32)), this, SLOT (remainingChanged (qint32)));
    connect (pom.get(), SIGNAL (stateChanged (State)), this, SLOT (stateChanged (State)));
    connect (&hotkeys, SIGNAL (activated (size_t)), this, SLOT (hotkeyPressed (size_t)));
    connect (settings.get(), SIGNAL (hotkeyStartChanged (QString)), this, SLOT (setHotkeys()));
    connect (settings.get(), SIGNAL (hotkeyStopChanged (QString)), this, SLOT (setHotkeys()));
    connect (settings.get(), SIGNAL (hotkeyPauseChanged (QString)), this, SLOT (setHotkeys()));
    //
    tray.show();
}

TrayIcon::~TrayIcon()
{
    delete mainwindow;
}

void TrayIcon::remainingChanged (qint32 rem)
{
    int minutes_rounded = std::ceil (1.* (rem % 3600) / 60);
    int hours = rem / 3600;
    int minutes = (rem % 3600) / 60;
    int seconds = rem % 60;
    switch (pom->state()) {
        case State::ACTIVE:
            paintText (QString::number (minutes_rounded));
            tray.setToolTip (tr ("Active\nTime remaining: %1 h %2 m %3 s").arg (hours).arg (minutes).arg (seconds));
            break;
        case State::SHORT_BREAK:
        case State::LONG_BREAK:
            tray.setToolTip (tr ("Break\nTime remaining: %1 h %2 m %3 s").arg (hours).arg (minutes).arg (seconds));
            paintText (QString::number (minutes_rounded), Qt::green);
            break;
        default:
            tray.setToolTip ("");
            break;
    }
}

void TrayIcon::stateChanged (State state)
{
    pixmap.load (":/icons/tomato.svg");
    switch (state) {
        case State::PAUSED:
            paintText ("॥");
            sounds->stopTickcing();
            menu.actions()[1]->setVisible (true);
            menu.actions()[1]->setText ("Continue");
            menu.actions()[0]->setVisible (false);
            break;
        case State::STOPPED:
            paintText ("");
            sounds->stopTickcing();
            menu.actions()[1]->setVisible (false);
            menu.actions()[2]->setVisible (false);
            menu.actions()[0]->setVisible (true);
            break;
        case State::ACTIVE:
            if (pom->prevState() == State::SHORT_BREAK ||
                    pom->prevState() == State::LONG_BREAK) {
                tray.showMessage (tr ("It's time for a new pomodoro"),
                                  tr ("Get to work!"));
                sounds->playNewPomodoro();
            }
            sounds->startTicking();
            if (settings->allowPause()) {
                menu.actions()[1]->setVisible (true);
                menu.actions()[1]->setText ("Pause");
            }
            menu.actions()[0]->setVisible (false);
            menu.actions()[2]->setVisible (true);
            break;
        case State::SHORT_BREAK:
        case State::LONG_BREAK:
            sounds->playBreak();
            sounds->stopTickcing();
            tray.showMessage (tr ("Take a break!"),
                              tr (""));
            menu.actions()[1]->setVisible (false);
            menu.actions()[0]->setVisible (true);
            break;
        default:
            sounds->stopTickcing();
            menu.actions()[1]->setVisible (true);
            menu.actions()[1]->setText ("Pause");
            menu.actions()[0]->setVisible (true);
            break;
    }
}

void TrayIcon::exit()
{
    QCoreApplication::exit();
}

void TrayIcon::trayActivated (QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
            if (mainwindow->isVisible()) mainwindow->hide();
            else mainwindow->show();
            break;
        default:
            break;
    }
}

void TrayIcon::showSettingsDialog()
{
    if (!settingsDialog) {
        settingsDialog = std::make_shared<SettingsDialog> (settings);
    }
    settingsDialog->show();
}

void TrayIcon::hotkeyPressed (size_t id)
{
    switch (id) {
        case HOTKEY_START:
            pom->start();
            break;
        case HOTKEY_PAUSE:
            pom->pause();
            break;
        case HOTKEY_STOP:
            pom->stop();
            break;
        default:
            break;
    }
}

void TrayIcon::setHotkeys()
{
    if (!settings->hotkeyStart().isEmpty())
        hotkeys.registerHotkey (settings->hotkeyStart(), HOTKEY_START);
    if (!settings->hotkeyStop().isEmpty())
        hotkeys.registerHotkey (settings->hotkeyStop(), HOTKEY_STOP);
    if (!settings->hotkeyPause().isEmpty())
        hotkeys.registerHotkey (settings->hotkeyPause(), HOTKEY_PAUSE);
}

void TrayIcon::paintText (QString text, QColor color)
{
    if (oldtext == text) return;
    pixmap.load (":/icons/tomato.svg");
    pixmap = pixmap.scaled (QSize (32, 32), Qt::KeepAspectRatio);
    if (!text.isEmpty()) {
        QPainter painter;
        painter.begin (&pixmap);
        painter.setPen (color);
        painter.setFont (QFont ("Droid Sans", 16));
        painter.drawText (QRectF (0, 0, 32, 32), Qt::AlignCenter, text);
        painter.end();
    }
    icon.addPixmap (pixmap);
    tray.setIcon (icon);
    oldtext = text;
}
