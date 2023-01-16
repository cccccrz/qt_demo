#ifndef APP_H
#define APP_H

#include <string>
#include <QObject>

namespace App {
    enum CMD {
        CMD_HEARTBEAT,
        CMD_QUIT
    };

    struct LiveDataHeader {
        uint len = 0;
        CMD cmd;
    };
    struct LiveData {
        LiveDataHeader header;
        std::string data;
    };

    static QString TargetAppName;           // 保护目标程序名称
    static int TargetPort = 6591;
    static int DaemonPort = 6601;
    static int HeartbeatInterval = 2000;    // 心跳间隔
    static int TimeoutCount = 3;            // 最大允许丢失次数
    static int RestartCount = 0;            // 已重启次数
    static bool RestartExplorer = false;    // 是否重启桌面

} // namespace App

#endif // APP_H
