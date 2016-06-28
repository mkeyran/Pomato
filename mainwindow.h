#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pomodoro.h>
#include <QApplication>
#include <memory>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::weak_ptr<Pomodoro> pom, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void exit();
    void pomodoroStateChanged(State state);
private:
    std::weak_ptr<Pomodoro> pom;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
