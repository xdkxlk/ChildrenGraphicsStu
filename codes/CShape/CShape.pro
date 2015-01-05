#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T16:38:01
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

INCLUDEPATH += "C:\Users\Administrator\Desktop\homework\ChildGraphicsV2\Common"
TARGET = CShape
TEMPLATE = lib

DEFINES += CSHAPE_LIBRARY

SOURCES += cshape.cpp

HEADERS += cshape.h\
        cshape_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
