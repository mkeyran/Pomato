#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(Pomodoro *pom, QWidget *parent) :
    QMainWindow(parent),
//    pom (3000, 2000, 1000,this),
    pom (pom),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->start, SIGNAL(clicked(bool)),pom, SLOT(start()));
    connect(ui->stop,SIGNAL(clicked(bool)),pom,SLOT(stop()));
    connect(ui->pause,SIGNAL(clicked(bool)),pom,SLOT(pause()));
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
