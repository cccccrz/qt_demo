QT -= gui

TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++17

SOURCES += \
    core.cpp

HEADERS += \
    core_global.h \
    core.h

win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../bin/debug
else:win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../bin/release
else:unix:!macx: DESTDIR = $$PWD/../bin/linux
