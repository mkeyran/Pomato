#include <QApplication>
#include <pomodoro.h>
#include <trayicon.h>
#include <mainwindow.h>

//TODO: Добавить звуки оповещений и тиков
//TODO: Добавить графический интерфейс
//TODO: Добавить настройки
//TODO: Добавить статистику
//TODO: Добавить задачи
//TODO: Добавить интеграцию с todo.txt
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TrayIcon m;
//    m.show();
    return app.exec();
}
