CONFIG += qmltypes
QML_IMPORT_NAME = Qml.Net
QML_IMPORT_MAJOR_VERSION = 1

HEADERS += \
    $$PWD/NetQPainter.h \
    $$PWD/QmlNetPaintedItem.h

SOURCES += \
    $$PWD/NetQPainter.cpp \
    $$PWD/QmlNetPaintedItem.cpp

INCLUDEPATH += \
    $$PWD
