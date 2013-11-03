#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T11:16:25
#
#-------------------------------------------------

QT       += network

QT       -= gui

INCLUDEPATH += .

TARGET = QDHTLib
TEMPLATE = lib

DEFINES += QDHTLIB_LIBRARY

SOURCES += QDHT.cpp \
    BootstrapTest.cpp \
    NodeID.cpp \
    DHTMessageHandler.cpp \
    DHTMessageSender.cpp

HEADERS += QDHT.h\
        qdhtlib_global.h \
    BootstrapTest.h \
    NodeID.h \
    DHTMessageHandler.h \
    DHTMessageSender.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

#Linkage for QBencode
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QBencode/release/ -lQBencode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QBencode/debug/ -lQBencode
else:unix: LIBS += -L$$OUT_PWD/../QBencode/ -lQBencode

INCLUDEPATH += $$PWD/../QBencode
DEPENDPATH += $$PWD/../QBencode
