#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pomodoro.h>
#include <trayicon.h>
#include <QApplication>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void exit();
private:
    Pomodoro pom;
    TrayIcon tray;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
