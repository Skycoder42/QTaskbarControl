TEMPLATE = app

QT += core gui widgets

TARGET = Example

include(../qtaskbarcontrol.pri)

HEADERS += \
	widget.h

SOURCES += \
	main.cpp \
	widget.cpp

FORMS += \
	widget.ui
