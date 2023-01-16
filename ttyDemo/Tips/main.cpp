#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    QFont font("微软雅黑");
    font.setPixelSize(14);
    a.setFont(font);

    MainWindow w;
    w.show();
    return a.exec();
}
