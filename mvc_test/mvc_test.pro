QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
SOURCES += \
    main.cpp \
    model/FileListModel.cpp \
    view/mainwindow.cpp

HEADERS += \
    common/PublicStructs.h \
    model/FileListModel.h \
    view/mainwindow.h

FORMS += \
    view/mainwindow.ui

TARGET = mvc_test
win32:CONFIG(debug, debug|release): {
    DESTDIR = $$PWD/bin/debug
} else:win32:CONFIG(release, debug|release): {
    DESTDIR = $$PWD/bin/release
}
