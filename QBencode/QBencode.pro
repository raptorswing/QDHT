#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T11:23:09
#
#-------------------------------------------------

QT       -= gui

TARGET = QBencode
TEMPLATE = lib

INCLUDEPATH += .

DEFINES += QBENCODE_LIBRARY

SOURCES += \
    BencodeNode.cpp \
    IntegerBencodeNode.cpp \
    ByteStringBencodeNode.cpp \
    ListBencodeNode.cpp \
    DictBencodeNode.cpp \
    BencodeNodeVisitor.cpp \
    Bencode.cpp \
    WriteBencodeNodeVisitor.cpp

HEADERS +=\
        qbencode_global.h \
    BencodeNode.h \
    IntegerBencodeNode.h \
    ByteStringBencodeNode.h \
    ListBencodeNode.h \
    DictBencodeNode.h \
    BencodeNodeVisitor.h \
    Bencode.h \
    WriteBencodeNodeVisitor.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
