#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "app.h"
#include "applive.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#if _MSC_VER
    QTextCodec* codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec* codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec* codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    QFont font("微软雅黑");
    font.setPixelSize(14);
    a.setFont(font);

    AppLive::GetInstace().start(App::TargetPort);

    MainWindow w;
    w.setWindowTitle("客户端localclient");
    w.show();
    return a.exec();
}
