#ifndef LOCALSOCKET_H
#define LOCALSOCKET_H

#include <QUdpSocket>
#include "app.h"

class LocalSocket : public QUdpSocket
{
public:
    explicit LocalSocket(QObject *parent = nullptr);

    bool send(const App::LiveData& live_data, const QHostAddress& host, quint16 port);
    App::LiveData read(QHostAddress* sender = nullptr, quint16* senderPort = nullptr);

private:
    App::LiveData parse(char* data, int len);
};

#endif // LOCALSOCKET_H
