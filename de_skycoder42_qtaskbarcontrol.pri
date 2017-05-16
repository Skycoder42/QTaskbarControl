HEADERS += \
	$$PWD/qtaskbarcontrol.h \
	$$PWD/qtaskbarcontrol_p.h

SOURCES += \
	$$PWD/qtaskbarcontrol.cpp

linux {
	QT += dbus
	HEADERS += $$PWD/qtaskbarcontrol_x11.h
	SOURCES += $$PWD/qtaskbarcontrol_x11.cpp
}

INCLUDEPATH += $$PWD
