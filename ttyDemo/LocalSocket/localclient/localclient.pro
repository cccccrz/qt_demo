QT       += core gui network widgets

CONFIG += c++17

INCLUDEPATH += ../include
INCLUDEPATH += ../../include

SOURCES += \
    ../include/localsocket.cpp \
    applive.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../include/app.h \
    ../../include/singleton.h \
    ../include/localsocket.h \
    applive.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../bin/debug
else:win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../bin/release
else:unix:!macx: DESTDIR = $$PWD/../bin/linux
