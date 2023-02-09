QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += $$PWD

SOURCES += \
    delegate/FileInfoDelegate.cpp \
    main.cpp \
    model/FileListModel.cpp \
    model/FileSortFilterProxyModel.cpp \
    view/mainwindow.cpp

HEADERS += \
    common/PublicStructs.h \
    delegate/FileInfoDelegate.h \
    model/FileListModel.h \
    model/FileSortFilterProxyModel.h \
    view/mainwindow.h

FORMS += \
    view/mainwindow.ui

TARGET = mvc_test
win32:CONFIG(debug, debug|release): {
    DESTDIR = $$PWD/bin/debug
} else:win32:CONFIG(release, debug|release): {
    DESTDIR = $$PWD/bin/release
}

