#include "daemon.h"
#include <QTimer>
#include <QStandardPaths>
#include "localsocket.h"
#include "core.h"

void Daemon::start()
{
    while (!socket_->bind(QHostAddress::LocalHost, App::DaemonPort)) {
        App::DaemonPort++;
    }
    connect(socket_, &QUdpSocket::readyRead, this, &Daemon::readData);
    timerHeart_->start();
}

void Daemon::SetTarget(const QString &appname)
{
    App::TargetAppName = appname;
}

void Daemon::sendHearData()
{
    App::LiveData live_data;
    live_data.data = "hello";
    live_data.header.cmd = App::CMD_HEARTBEAT;
    live_data.header.len = live_data.data.length();
    bool ok = socket_->send(live_data, QHostAddress::LocalHost, App::TargetPort);
    qDebug() << "send heardata " << ok;

    if (ok_) {
        // reset flag
        lost_count_ = 0;
        ok_ = false;
    } else {
        lost_count_++;
    }

    if (lost_count_ > App::TimeoutCount) {
        if (IsProcessExist(App::TargetAppName)) {
            // 杀掉还是过滤？
            return;
        }

        timerHeart_->stop();
        killApp();

        QTimer::singleShot(1000, this, &Daemon::killOther);
        QTimer::singleShot(3000, this, &Daemon::StartApp);
        QTimer::singleShot(4000, this, &Daemon::StartExplorer);
    }
}

void Daemon::readData()
{
    do {
        QHostAddress sender;
        quint16 senderPort;
        App::LiveData live_data = socket_->read(&sender, &senderPort);
        if (live_data.header.len > 0) {
            if (App::CMD_HEARTBEAT == live_data.header.cmd) {
                lost_count_ = 0;
                ok_ = true;
            } else if (App::CMD_QUIT == live_data.header.cmd) {
                qApp->quit();
            }
            // TODO other cmd
        }
    } while (socket_->hasPendingDatagrams());
}

void Daemon::killApp()
{
    KillProcess(App::TargetAppName);
}

void Daemon::killOther()
{
#ifdef Q_OS_WIN
    KillProcess("WerFault");

    // 重建缓存，彻底清除托盘图标
    if (App::RestartExplorer) {
        KillProcess("explorer");
    }
#endif
}

void Daemon::StartApp()
{
    lost_count_ = 0;
    ok_ = true;
    QStringList args; // todo
    StartProcess(App::TargetAppName, args);
    timerHeart_->start();

    App::RestartCount++;
}

void Daemon::StartExplorer()
{
#ifdef Q_OS_WIN
    QString str = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    if (App::RestartExplorer) {
        str = QString("%1\\Windows\\explorer.exe").arg(str.mid(0, 2));
        QProcess::startDetached(str);
    }
#endif
}

Daemon::Daemon(QObject *parent)
    : QObject{parent}
{
    socket_ = new LocalSocket(this);
    timerHeart_ = new QTimer(this);
    timerHeart_->setInterval(App::HeartbeatInterval);
    connect(timerHeart_, &QTimer::timeout, this, &Daemon::sendHearData);
}
