#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T12:49:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalculatorParser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    expressionelement.cpp \
    stringcalculator.cpp \
    unittester.cpp \
    inputrenderer.cpp

HEADERS  += mainwindow.h \
    expressionelement.h \
    stringcalculator.h \
    unittester.h \
    inputrenderer.h
         expressionelement.h

FORMS    += mainwindow.ui

CONFIG += c++11
