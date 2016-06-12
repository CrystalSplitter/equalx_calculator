#-------------------------------------------------
#
# Project created by QtCreator 2015-12-16T16:46:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = equalx_source
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    expressionelement.cpp \
    stringcalculator.cpp

HEADERS  += mainwindow.h \
    expressionelement.h \
    operation.h \
    stringcalculator.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

