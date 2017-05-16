#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T17:24:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Example
TEMPLATE = app

include(../de_skycoder42_qtaskbarcontrol.pri)

DEFINES += QT_DEPRECATED_WARNING

SOURCES += main.cpp\
		widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
