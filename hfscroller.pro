#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T09:44:06
#
#-------------------------------------------------

mac {
QMAKE_MAC_SDK = macosx10.9
LIBS += -framework ApplicationServices
}

QMAKE_CXXFLAGS += -std=c++11
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hfscroller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eventgenerator.cpp

HEADERS  += mainwindow.h \
    eventgenerator.h

FORMS    += mainwindow.ui
