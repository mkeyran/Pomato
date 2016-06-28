#include "trayicon.h"
#include <QPainter>
#include <math.h>
#include <QApplication>
#include <mainwindow.h>
#include <QDebug>
TrayIcon::TrayIcon(QObject *parent) : QObject(parent)
{
    pom = std::make_shared<Pomodoro>(this);
    mainwindow = new MainWindow(pom);
    settings = new Settings(pom, this);
    connect(pom.get(),SIGNAL(remainingChanged(qint32)),this,SLOT(remainingChanged(qint32)));
    connect(pom.get(),SIGNAL(stateChanged(State)),this,SLOT(stateChanged(State)));
    pixmap.load(":/icons/tomato.svg");
    icon.addPixmap(pixmap.scaled(QSize(32,32),Qt::KeepAspectRatio));
    tray.setIcon(icon);
    menu.addAction (tr ("Start"),this->pom.get(),SLOT(start()));
    menu.addAction (tr ("Pause"),this->pom.get(),SLOT(pause()));
    menu.actions()[1]->setVisible(false);
    menu.addAction (tr ("Stop"),this->pom.get(),SLOT(stop()));
    menu.actions()[2]->setVisible(false);
    menu.addSeparator();
    menu.addAction (tr ("Exit"), this, SLOT(exit()));
    tray.setContextMenu(&menu);
    connect(&tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
    tray.show();
}

TrayIcon::~TrayIcon()
{
    delete mainwindow;
}

void TrayIcon::remainingChanged(qint32 rem)
{
    int minutes_rounded = std::ceil(1.*(rem%3600)/60);
    int hours = rem/3600;
    int minutes = (rem%3600)/60;
    int seconds = rem%60;

    switch (pom->state()) {
    case State::ACTIVE:
        paintText(QString::number(minutes_rounded));
        tray.setToolTip(tr("Active\nTime remaining: %1 h %2 m %3 s").arg(hours).arg(minutes).arg(seconds));
        break;
    case State::SHORT_BREAK:
    case State::LONG_BREAK:
        paintText(QString::number(minutes_rounded),Qt::green);
        break;
    default:
        break;
    }
}

void TrayIcon::stateChanged(State state)
{
    pixmap.load(":/icons/tomato.svg");
    switch (state) {
    case State::PAUSED:
        paintText("॥");
        menu.actions()[1]->setVisible(true);
        menu.actions()[1]->setText("Continue");
        menu.actions()[0]->setVisible(false);
        break;
    case State::STOPPED:
        paintText("");
        menu.actions()[1]->setVisible(false);
        menu.actions()[2]->setVisible(false);
        menu.actions()[0]->setVisible(true);
        break;
    case State::ACTIVE:
        if (pom->prevState() == State::SHORT_BREAK||
                pom->prevState() == State::LONG_BREAK)
            tray.showMessage(tr("It's time for a new pomodoro"),
                             tr("Get to work!"));
        if (pom->pauseIsAllowed()){
            menu.actions()[1]->setVisible(true);
            menu.actions()[1]->setText("Pause");
        }
        menu.actions()[0]->setVisible(false);
        menu.actions()[2]->setVisible(true);
        break;
    case State::SHORT_BREAK:
    case State::LONG_BREAK:
        tray.showMessage(tr("Have a break!"),
                         tr(""));
        menu.actions()[1]->setVisible(false);
        menu.actions()[0]->setVisible(true);
        break;
    default:
        menu.actions()[1]->setVisible(true);
        menu.actions()[1]->setText("Pause");
        menu.actions()[0]->setVisible(true);
        break;
    }
}

void TrayIcon::exit()
{
    QCoreApplication::exit();
}

void TrayIcon::trayActivated(QSystemTrayIcon::ActivationReason reason)
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



void TrayIcon::paintText(QString text, QColor color)
{
    if (oldtext==text) return;
    pixmap.load(":/icons/tomato.svg");
    pixmap = pixmap.scaled(QSize(32,32),Qt::KeepAspectRatio);
    if (!text.isEmpty()){
        QPainter painter;
        painter.begin(&pixmap);
        painter.setPen(color);
        painter.setFont(QFont("Droid Sans",16));
        painter.drawText(QRectF(0,0,32,32),Qt::AlignCenter,text);
        painter.end();
    }
    icon.addPixmap(pixmap);
    tray.setIcon(icon);
    oldtext = text;
}
