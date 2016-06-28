#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
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
    }
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
