#include "applive.h"
#include <QApplication>
#include <QTime>
#include "localsocket.h"

#define TIMEMS qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))

bool AppLive::start(int port)
{
    bool ok = socket_->bind(QHostAddress::LocalHost, port);
    if (ok) {
        connect(socket_, &QUdpSocket::readyRead, this, &AppLive::readData);
        qDebug() << TIMEMS << "Start AppLive Ok";
    }
    return ok;
}

bool AppLive::quitDaemon()
{
    App::LiveData live_data;
    live_data.header.cmd = App::CMD_QUIT;
    live_data.data = "quit";
    live_data.header.len = live_data.data.length();
    return socket_->send(live_data, QHostAddress::LocalHost, App::DaemonPort);
}

void AppLive::stop()
{
    socket_->abort();
    socket_->disconnect(this);
}

void AppLive::readData()
{
    do {
        QHostAddress sender;
        quint16 senderPort;
        App::LiveData live_data = socket_->read(&sender, &senderPort);
        if (live_data.header.len > 0) {
            QString reply = QString::fromStdString(live_data.data);
            qDebug() << TIMEMS << " revice " << reply;
            if (App::CMD_HEARTBEAT == live_data.header.cmd && reply == "hello") {
                App::DaemonPort = senderPort;
                live_data.data = QString("%1OK").arg(qApp->applicationFilePath()).toStdString();
                live_data.header.cmd = App::CMD_HEARTBEAT;
                live_data.header.len = live_data.data.length();
                bool ok = socket_->send(live_data, sender, senderPort);
                qDebug() << TIMEMS << " send " << live_data.data.c_str() << " " << ok;
            }
        }
    } while (socket_->hasPendingDatagrams());
}

AppLive::AppLive(QObject *parent) : QObject(parent), socket_(new LocalSocket(this))
{
}
