QT       += core gui network widgets

CONFIG += c++17

INCLUDEPATH += ../include
INCLUDEPATH += ../../include

SOURCES += \
    ../include/localsocket.cpp \
    daemon.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../include/app.h \
    ../include/localsocket.h \
    daemon.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../bin/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../bin/debug/ -lcore
else:unix:!macx: LIBS += -L$$OUT_PWD/../../bin/linux/ -lcore

INCLUDEPATH += $$PWD/../../core
DEPENDPATH += $$PWD/../../core

win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../bin/debug
else:win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../bin/release
else:unix:!macx: DESTDIR = $$PWD/../bin/linux
