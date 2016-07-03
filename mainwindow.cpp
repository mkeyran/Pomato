#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPalette>
#include <math.h>
MainWindow::MainWindow(std::weak_ptr<Pomodoro> pom, QWidget *parent) :
    QMainWindow(parent),
    //    pom (3000, 2000, 1000,this),
    pom (pom),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto pom_locked = pom.lock();
    if (pom_locked){
        connect(ui->start, SIGNAL(clicked(bool)),pom_locked.get(), SLOT(start()));
        connect(ui->stop,SIGNAL(clicked(bool)),pom_locked.get(),SLOT(stop()));
        connect(ui->pause,SIGNAL(clicked(bool)),pom_locked.get(),SLOT(pause()));
        connect(pom_locked.get(),SIGNAL(stateChanged(State)),this,SLOT(pomodoroStateChanged(State)));
        connect(pom_locked.get(),SIGNAL(remainingChanged(qint32)),this, SLOT(showRemaining(qint32)));
    }
    connect(ui->settings, SIGNAL(clicked(bool)),this,SIGNAL(showSettings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    qDebug()<<"exit()";
    QApplication::exit();
}

void MainWindow::pomodoroStateChanged(State state)
{
    Q_UNUSED(state);
}

void MainWindow::showRemaining(qint32 rem)
{
    int hours = rem/3600;
    int minutes = (rem%3600)/60;
    int seconds = rem%60;
    auto pom_locked = pom.lock();
    if (pom_locked){
        QPalette palette = ui->label->palette();
        switch (pom_locked->state()) {
        case State::ACTIVE:
            ui->label->setText(tr("%1:%2:%3").arg(hours,2,10,QLatin1Char('0'))
                               .arg(minutes,2,10,QLatin1Char('0'))
                               .arg(seconds,2,10,QLatin1Char('0')));
            palette.setColor(QPalette::WindowText, Qt::red);
            ui->label->setPalette(palette);
            break;
        case State::SHORT_BREAK:
        case State::LONG_BREAK:
        case State::PAUSED:
            ui->label->setText(tr("%1:%2:%3").arg(hours,2,10,QLatin1Char('0'))
                               .arg(minutes,2,10,QLatin1Char('0'))
                               .arg(seconds,2,10,QLatin1Char('0')));
            palette.setColor(QPalette::WindowText, Qt::green);
            ui->label->setPalette(palette);
            break;
        default:
            ui->label->setText(tr("--:--:--"));
            palette.setColor(QPalette::WindowText, Qt::green);
            ui->label->setPalette(palette);
            break;
        }
    }
}

void MainWindow::allowPauseChanged(bool allow)
{
    ui->pause->setEnabled(allow);
}
