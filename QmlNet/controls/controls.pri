CONFIG += qmltypes
QML_IMPORT_NAME = Qml.Net
QML_IMPORT_MAJOR_VERSION = 1

HEADERS += \
    $$PWD/QmlNetPaintedItem.h \
    $$PWD/INetQPainter.h

SOURCES += \
    $$PWD/QmlNetPaintedItem.cpp \
    $$PWD/INetQPainter.cpp

INCLUDEPATH += \
    $$PWD
