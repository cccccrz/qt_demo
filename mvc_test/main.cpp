#include "view/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
#if QT_VERSION > QT_VERSION_CHECK(5, 15, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
