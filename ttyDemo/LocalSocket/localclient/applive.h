#ifndef APPLIVE_H
#define APPLIVE_H

#include <QObject>
#include "singleton.h"

class LocalSocket;
class AppLive : public QObject, public Singleton<AppLive>
{
    Q_OBJECT
    friend class Singleton<AppLive>;
public slots:
    bool start(int port);
    bool quitDaemon();
    void stop();

private slots:
    void readData();

private:
    explicit AppLive(QObject* parent = Q_NULLPTR);

    LocalSocket* socket_;
};

#endif // APPLIVE_H
