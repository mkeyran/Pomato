#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),pom (this),
    tray(&pom, this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->start, SIGNAL(clicked(bool)),&pom, SLOT(start()));
    connect(ui->stop,SIGNAL(clicked(bool)),&pom,SLOT(stop()));
    connect(ui->pause,SIGNAL(clicked(bool)),&pom,SLOT(pause()));
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
