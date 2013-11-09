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
    interfaces\DHTMessageHandler.cpp \
    interfaces\DHTMessageSender.cpp \
    DefaultMessageHandler.cpp \
    IPPort.cpp

HEADERS += QDHT.h\
        qdhtlib_global.h \
    BootstrapTest.h \
    NodeID.h \
    interfaces\DHTMessageHandler.h \
    interfaces\DHTMessageSender.h \
    DefaultMessageHandler.h \
    IPPort.h \
    ttmath/ttmathuint_x86_64.h \
    ttmath/ttmathuint_x86.h \
    ttmath/ttmathuint_noasm.h \
    ttmath/ttmathuint.h \
    ttmath/ttmathtypes.h \
    ttmath/ttmaththreads.h \
    ttmath/ttmathparser.h \
    ttmath/ttmathobjects.h \
    ttmath/ttmathint.h \
    ttmath/ttmathdec.h \
    ttmath/ttmathbig.h \
    ttmath/ttmath.h \
    ttmath/ttmathmisc.h

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

OTHER_FILES += \
    ttmath/ttmathuint_x86_64_msvc.asm
