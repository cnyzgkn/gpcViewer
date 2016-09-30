#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T14:11:57
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gpcViewerQt
TEMPLATE = app


SOURCES += ..\gpcCore\gpc.c \
    main.cpp\
    gpcwrapper.cpp \
    gpcglwidget.cpp \
    mainwindow.cpp \

HEADERS  += ..\gpcCore\gpc.h \
    gpcwrapper.h \
    gpcglwidget.h \
    mainwindow.h \



FORMS    += mainwindow.ui
