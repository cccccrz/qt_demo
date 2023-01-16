#ifndef DAEMON_H
#define DAEMON_H

#include <QObject>
#include "singleton.h"

class LocalSocket;
class QTimer;
class Daemon : public QObject, public Singleton<Daemon>
{
    Q_OBJECT
    friend class Singleton<Daemon>;
public slots:
    void start();
    void SetTarget(const QString& appname);

private slots:
    void sendHearData();
    void readData();
    void killApp();
    void killOther();
    void StartApp();
    void StartExplorer();

private:
    explicit Daemon(QObject *parent = nullptr);

    LocalSocket* socket_;
    QTimer* timerHeart_;
    bool ok_ = false;
    int lost_count_ = 0;
};

#endif // DAEMON_H
