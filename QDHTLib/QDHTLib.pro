#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T11:16:25
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = QDHTLib
TEMPLATE = lib

DEFINES += QDHTLIB_LIBRARY

SOURCES += QDHT.cpp \
    BootstrapTest.cpp

HEADERS += QDHT.h\
        qdhtlib_global.h \
    BootstrapTest.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
