HEADERS += \
	$$PWD/qtaskbarcontrol.h \
	$$PWD/qtaskbarcontrol_p.h

SOURCES += \
	$$PWD/qtaskbarcontrol.cpp

linux {
	QT += dbus
	HEADERS += $$PWD/qtaskbarcontrol_x11.h
	SOURCES += $$PWD/qtaskbarcontrol_x11.cpp
} else:win32 {
	QT += winextras
	HEADERS += $$PWD/qtaskbarcontrol_win.h
	SOURCES += $$PWD/qtaskbarcontrol_win.cpp
}

INCLUDEPATH += $$PWD
