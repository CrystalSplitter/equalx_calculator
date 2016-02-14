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
        stringcalculator.cpp \
    expressionelement.cpp \
    utilities.cpp

HEADERS  += mainwindow.h \
    operation.h \
    expressionelement.h \
    stringcalculator.h \
    utilities.h
         expressionelement.h

FORMS    += mainwindow.ui
