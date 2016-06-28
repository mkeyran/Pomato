#ifndef TRAYICON_H
#define TRAYICON_H
#include <QSystemTrayIcon>
#include <QPixmap>
#include <pomodoro.h>
#include <QIcon>
#include <QMenu>
#include <QMediaPlayer>
#include <mainwindow.h>
class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = 0);
    ~TrayIcon();
signals:
public slots:
    void remainingChanged(qint32 rem);
    void stateChanged(State state);
    void exit();
    void trayActivated(QSystemTrayIcon::ActivationReason reason);
private:
    void paintText(QString text, QColor color=Qt::white);
    Pomodoro* pom;
    QSystemTrayIcon tray;
    QPixmap pixmap;
    QIcon icon;
    QString oldtext;
    QMenu menu;
    QMediaPlayer notification;
    QMediaPlayer ticks;
    MainWindow *mainwindow;

};

#endif // TRAYICON_H
