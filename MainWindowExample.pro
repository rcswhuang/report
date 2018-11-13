#-------------------------------------------------
#
# Project created by QtCreator 2017-09-21T14:04:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SARibbonMainWindowExample
TEMPLATE = app
DESTDIR = ..\..\bin
INCLUDEPATH += \
              ..\SARibbonBar

SOURCES += main.cpp\
    mainwindow.cpp \ 
    hreportwindowact.cpp

HEADERS  += \
    mainwindow.h 

RESOURCES += \
    saribbonresouce.qrc


LIBS += -L..\..\lib -lH5RibbonBar
