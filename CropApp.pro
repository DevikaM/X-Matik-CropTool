#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T22:11:59
#
#-------------------------------------------------
QT += core gui widgets#include <QWidget>

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_video  -lopencv_videoio  -lopencv_videostab

TARGET = CropApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
