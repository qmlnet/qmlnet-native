CONFIG += qmltypes
QML_IMPORT_NAME = Qml.Net
QML_IMPORT_MAJOR_VERSION = 1

HEADERS += \
    $$PWD/INetQPainter.h \
    $$PWD/NetQPainter.h \
    $$PWD/QmlNetRecordingPaintedItem.h \
    $$PWD/QmlNetPaintedItem.h

SOURCES += \
    $$PWD/INetQPainter.cpp \
    $$PWD/NetQPainter.cpp \
    $$PWD/QmlNetRecordingPaintedItem.cpp \
    $$PWD/QmlNetPaintedItem.cpp

INCLUDEPATH += \
    $$PWD
