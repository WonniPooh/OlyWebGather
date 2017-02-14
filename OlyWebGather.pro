#-------------------------------------------------
#
# Project created by QtCreator 2017-01-26T19:55:02
#
#-------------------------------------------------

CONFIG   += c++11

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OlyWebGather
TEMPLATE = app


SOURCES += main.cpp\
    jsonhandler.cpp \
    assetstatus.cpp \
    parsecookies.cpp \
    assetstatusbar.cpp \
    mainclass.cpp \
    requestmanager.cpp

HEADERS  += \
    jsonhandler.h \
    assetstatus.h \
    parsecookies.h \
    assetstatusbar.h \
    mainclass.h \
    requestmanager.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-TcpClient-Desktop_Qt_5_5_1_GCC_64bit-Debug/release/ -lTcpClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-TcpClient-Desktop_Qt_5_5_1_GCC_64bit-Debug/debug/ -lTcpClient
else:unix: LIBS += -L$$PWD/../build-TcpClient-Desktop_Qt_5_5_1_GCC_64bit-Debug/ -lTcpClient

INCLUDEPATH += $$PWD/../TcpClient
DEPENDPATH += $$PWD/../build-TcpClient-Desktop_Qt_5_5_1_GCC_64bit-Debug
