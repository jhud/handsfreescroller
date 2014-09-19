#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T09:44:06
#
#-------------------------------------------------

mac {
message("Using mac configuration")
QMAKE_MAC_SDK = macosx10.9
LIBS += -framework ApplicationServices
}

unix {
message("Using unix configuration")
OPENCV_PATH = /opt/local/include/opencv2

LIBS += -L/opt/local/lib
LIBS += -lopencv_core \
        -lopencv_highgui \
        -lopencv_video \
        -lopencv_imgproc

}

QMAKE_CXXFLAGS += -std=c++11
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /opt/local/include

TARGET = hfscroller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eventgenerator.cpp \
    cqtopencvviewergl.cpp

HEADERS  += mainwindow.h \
    eventgenerator.h \
    cqtopencvviewergl.h

FORMS    += mainwindow.ui
