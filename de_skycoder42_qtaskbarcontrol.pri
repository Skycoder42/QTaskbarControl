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
	RESOURCES += $$PWD/qtaskbarcontrol.qrc
} else:mac {
	QT += macextras
	LIBS += -framework AppKit
	HEADERS += $$PWD/qtaskbarcontrol_mac.h
	OBJECTIVE_SOURCES += $$PWD/qtaskbarcontrol_mac.mm
}

INCLUDEPATH += $$PWD


