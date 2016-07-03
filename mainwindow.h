#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pomodoro.h>
#include <QApplication>
#include <memory>
#include <settings.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::weak_ptr<Pomodoro> pom, std::shared_ptr<Settings> settings, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void exit();
    void pomodoroStateChanged(State state);
    void showRemaining(qint32 rem);
    void allowPauseChanged(bool allow);
signals:
    void showSettings();
private:
    std::weak_ptr<Pomodoro> pom;
    Ui::MainWindow *ui;
    std::shared_ptr<Settings> settings;
};

#endif // MAINWINDOW_H
