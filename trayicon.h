#ifndef TRAYICON_H
#define TRAYICON_H
#include <QSystemTrayIcon>
#include <QPixmap>
#include <pomodoro.h>
#include <QIcon>
#include <QMenu>
class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(Pomodoro* pom, QObject *parent = 0);

signals:
public slots:
    void remainingChanged(qint32 rem);
    void statusChanged(Status status);
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
};

#endif // TRAYICON_H
