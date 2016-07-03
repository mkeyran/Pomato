#include <QApplication>
#include <pomodoro.h>
#include <trayicon.h>
#include <mainwindow.h>

//TODO: Добавить звуки оповещений и тиков
//TODO: Добавить глобальные хоткеи
//TODO: Добавить графический интерфейс
//TODO: Добавить настройки
//TODO: Добавить статистику
//TODO: Добавить задачи
//TODO: Добавить интеграцию с todo.txt
//TODO: Добавить поддержку темной и светлой тем
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TrayIcon m;
//    m.show();
    return app.exec();
}
