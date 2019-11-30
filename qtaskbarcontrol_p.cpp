#include "qtaskbarcontrol_p.h"
#include <QIcon>

void QTaskbarControlPrivate::setWindow(QWindow *window)
{
	Q_UNUSED(window)
}

void QTaskbarControlPrivate::setWindowsProgressState(QTaskbarControl::WinProgressState state)
{
	Q_UNUSED(state)
}

QTaskbarControl::WinProgressState QTaskbarControlPrivate::windowsProgressState() const
{
	return QTaskbarControl::Stopped;
}

void QTaskbarControlPrivate::setWindowsBadgeIcon(const QIcon &icon)
{
	Q_UNUSED(icon)
}

QIcon QTaskbarControlPrivate::windowsBadgeIcon() const
{
	return {};
}

void QTaskbarControlPrivate::setWindowsBadgeTextColor(const QColor &color)
{
	Q_UNUSED(color)
}

QColor QTaskbarControlPrivate::windowsBadgeTextColor() const
{
	return {};
}
