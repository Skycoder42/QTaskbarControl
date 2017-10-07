PUBLIC_HEADERS += \
	$$PWD/qtaskbarcontrol.h

HEADERS += $$PUBLIC_HEADERS \
	$$PWD/qtaskbarcontrol_p.h

SOURCES += \
	$$PWD/qtaskbarcontrol.cpp

linux {
	HEADERS += $$PWD/qtaskbarcontrol_x11.h
	SOURCES += $$PWD/qtaskbarcontrol_x11.cpp
} else:win32 {
	HEADERS += $$PWD/qtaskbarcontrol_win.h
	SOURCES += $$PWD/qtaskbarcontrol_win.cpp
	RESOURCES += $$PWD/qtaskbarcontrol.qrc
} else:mac {
	HEADERS += $$PWD/qtaskbarcontrol_mac.h
	OBJECTIVE_SOURCES += $$PWD/qtaskbarcontrol_mac.mm
}

INCLUDEPATH += $$PWD

include($$PWD/de_skycoder42_qtaskbarcontrol.prc)
