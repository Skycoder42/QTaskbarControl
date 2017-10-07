linux: QT += dbus
else:win32: QT += winextras
else:mac {
	QT += macextras
	LIBS += -framework AppKit
}
