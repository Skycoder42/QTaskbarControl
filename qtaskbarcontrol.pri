HEADERS += \
	$$PWD/qtaskbarcontrol.h \
	$$PWD/qtaskbarcontrol_p.h

SOURCES += \
	$$PWD/qtaskbarcontrol.cpp

linux:!android:!emscripten {
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
} else {
	HEADERS += $$PWD/qtaskbarcontrol_dummy.h
	SOURCES += $$PWD/qtaskbarcontrol_dummy.cpp
}

INCLUDEPATH += $$PWD

QDEP_PACKAGE_EXPORTS += Q_TASKBAR_CONTROL_EXPORT
!qdep_build: DEFINES += "Q_TASKBAR_CONTROL_EXPORT="
