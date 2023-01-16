#include "localsocket.h"
#include <QNetworkProxy>

const quint16 MAXSIZE = 512;

LocalSocket::LocalSocket(QObject *parent) : QUdpSocket{parent}
{
    // win7 绑定阻塞
    setProxy(QNetworkProxy::NoProxy);
}

bool LocalSocket::send(const App::LiveData &live_data, const QHostAddress &host, quint16 port)
{
    uint head_len = sizeof (App::LiveDataHeader);
    uint data_len = head_len+live_data.header.len+1;
    if (data_len > MAXSIZE) return false;
    char buff[MAXSIZE] = {0};
    memcpy(buff, (char*)&live_data.header, head_len);
    memcpy(buff+head_len, live_data.data.c_str(), live_data.header.len);
    qint64 send_len = this->writeDatagram(buff, data_len, host, port);

    return send_len == data_len;
}

App::LiveData LocalSocket::read(QHostAddress *sender, quint16 *senderPort)
{
    QByteArray tempData;
    tempData.resize(this->pendingDatagramSize());
    this->readDatagram(tempData.data(), tempData.size(), sender, senderPort);

    return this->parse(tempData.data(), tempData.size());
}

App::LiveData LocalSocket::parse(char *data, int len)
{
    App::LiveData live_data;
    int head_len = sizeof (App::LiveDataHeader);
    if (len < head_len) return live_data;
    memcpy(&live_data.header, data, head_len);
    live_data.header.len = live_data.header.len > MAXSIZE ? MAXSIZE : live_data.header.len;
    if ((uint)len < head_len + live_data.header.len) return live_data;
    char buff[MAXSIZE] = {0};
    memcpy(buff, data+head_len, live_data.header.len);
    live_data.data = buff;

    return live_data;
}
