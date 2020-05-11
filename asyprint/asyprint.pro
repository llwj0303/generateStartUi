#-------------------------------------------------
#
# Project created by QtCreator 2020-05-11T14:58:12
#
#-------------------------------------------------

QT       += core gui xml printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = asyprint
TEMPLATE = app

RC_ICONS = icon/main.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    configapp.cpp \
    iconhelper.cpp

HEADERS  += mainwindow.h \
    configapp.h \
    myhelper.h \
    iconhelper.h

FORMS    += mainwindow.ui

INCLUDEPATH += ./qrcode/libpng \
               ./qrcode/zlib

LIBS += -L./lib
LIBS += -llibpng -lzlib
LIBS += -llibqrencode

RESOURCES += \
    rc.qrc
