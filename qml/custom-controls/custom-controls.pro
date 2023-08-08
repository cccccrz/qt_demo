QT += quick

SOURCES += \
        main.cpp

RESOURCES += qml/TControls/TControls.qrc \
    qml/qml.qrc \
    images/res.qrc

# test controls
# DEFINES += TEST_TBTN

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
