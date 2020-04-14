#-------------------------------------------------
#
# Project created by QtCreator 2020-04-14T15:58:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ImageProc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $(home)/dariamityagina/Documents/opencv/include
LIBS += -L$(home)/dariamityagina/Documents/opencv/lib/

LIBS += -lopencv_core \
        -lopencv_imgproc \
        -lopencv_imgcodecs \
        -lopencv_highgui \
        -lopencv_objdetect

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    methods.cpp

HEADERS += \
        mainwindow.h \
    methods.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    moment.jpg \
    play.jpg \
    a.jpg
