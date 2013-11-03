#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T11:17:10
#
#-------------------------------------------------

QT       += core network

QT       -= gui

INCLUDEPATH += .

TARGET = TestApp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

#Linkage for QDHTLib
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QDHTLib/release/ -lQDHTLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QDHTLib/debug/ -lQDHTLib
else:unix: LIBS += -L$$OUT_PWD/../QDHTLib/ -lQDHTLib

INCLUDEPATH += $$PWD/../QDHTLib
DEPENDPATH += $$PWD/../QDHTLib

#Linkage for QBencode
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QBencode/release/ -lQBencode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QBencode/debug/ -lQBencode
else:unix: LIBS += -L$$OUT_PWD/../QBencode/ -lQBencode

INCLUDEPATH += $$PWD/../QBencode
DEPENDPATH += $$PWD/../QBencode
