QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tips.cpp

HEADERS += \
    mainwindow.h \
    tips.h

FORMS += \
    mainwindow.ui

win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../bin/debug
else:win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../bin/release
else:unix:!macx: DESTDIR = $$PWD/../bin/linux

