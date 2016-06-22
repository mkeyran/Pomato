#include "trayicon.h"
#include <QPainter>
#include <math.h>
#include <QApplication>
#include <mainwindow.h>
#include <QDebug>
TrayIcon::TrayIcon(Pomodoro *pom, QObject *parent) : QObject(parent)
{
    this->pom=pom;
    connect(pom,SIGNAL(remainingChanged(qint32)),this,SLOT(remainingChanged(qint32)));
    connect(pom,SIGNAL(statusChanged(Status)),this,SLOT(statusChanged(Status)));
    pixmap.load(":/icons/tomato.svg");
    icon.addPixmap(pixmap.scaled(QSize(32,32),Qt::KeepAspectRatio));
    tray.setIcon(icon);
    menu.addAction (tr ("Start"),this->pom,SLOT(start()));
    menu.addAction (tr ("Pause"),this->pom,SLOT(pause()));
    menu.actions()[1]->setVisible(false);
    menu.addAction (tr ("Stop"),this->pom,SLOT(stop()));
    menu.addSeparator();
    menu.addAction (tr ("Exit"), this, SLOT(exit()));
    tray.setContextMenu(&menu);
    connect(&tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
    tray.show();
}

void TrayIcon::remainingChanged(qint32 rem)
{
    int minutes_rounded = std::ceil(1.*(rem%3600)/60);
    int hours = rem/3600;
    int minutes = (rem%3600)/60;
    int seconds = rem%60;

    switch (pom->status()) {
    case Status::ACTIVE:
        paintText(QString::number(minutes_rounded));
        tray.setToolTip(tr("Active\nTime remaining: %1 h %2 m %3 s").arg(hours).arg(minutes).arg(seconds));
        break;
    case Status::SHORT_BREAK:
    case Status::LONG_BREAK:
        paintText(QString::number(minutes_rounded),Qt::green);
        break;
    default:
        break;
    }
}

void TrayIcon::statusChanged(Status status)
{
    pixmap.load(":/icons/tomato.svg");
    switch (status) {
    case Status::PAUSED:
        paintText("॥");
        menu.actions()[1]->setVisible(true);
        menu.actions()[1]->setText("Continue");
        break;
    case Status::STOPPED:
        paintText("");
        menu.actions()[1]->setVisible(false);
        break;
    default:
        menu.actions()[1]->setVisible(true);
        menu.actions()[1]->setText("Pause");
        break;
    }
}

void TrayIcon::exit()
{
    QCoreApplication::exit();
}

void TrayIcon::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
    MainWindow * par = qobject_cast<MainWindow*>(parent());
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if (par->isVisible()) par->hide();
        else par->show();
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
