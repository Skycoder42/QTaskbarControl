#include "qtaskbarcontrol.h"
#include "qtaskbarcontrol_p.h"

#include <QEvent>
#include <QWidget>
#include <QIcon>

QTaskbarControl::QTaskbarControl(QObject *parent) :
	QObject{parent},
	d{QTaskbarControlPrivate::createPrivate(this)}
{}

void QTaskbarControl::setWidget(QWidget *widget)
{
	if (widget && widget->windowHandle()) {
		setWindow(widget->windowHandle());
		return;
	}

	if (d->watchedWidget)
		d->watchedWidget->removeEventFilter(this);

	d->watchedWidget = widget;

	if (d->watchedWidget)
		d->watchedWidget->installEventFilter(this);
}

void QTaskbarControl::setWindow(QWindow *window)
{
	setWidget(nullptr);
	d->setWindow(window);
}

QTaskbarControl::~QTaskbarControl() = default;

QTaskbarControl::WinProgressState QTaskbarControl::windowsProgressState() const
{
	return d->windowsProgressState();
}

QIcon QTaskbarControl::windowsBadgeIcon() const
{
	return d->windowsBadgeIcon();
}

QColor QTaskbarControl::windowsBadgeTextColor() const
{
	return d->windowsBadgeTextColor();
}

bool QTaskbarControl::progressVisible() const
{
	return d->progressVisible;
}

double QTaskbarControl::progress() const
{
	return d->progress;
}

bool QTaskbarControl::counterVisible() const
{
	return d->counterVisible;
}

int QTaskbarControl::counter() const
{
	return d->counter;
}

void QTaskbarControl::setWindowsProgressState(QTaskbarControl::WinProgressState state)
{
	d->setWindowsProgressState(state);
}

void QTaskbarControl::setWindowsBadgeIcon(const QIcon &icon)
{
	d->setWindowsBadgeIcon(icon);
}

void QTaskbarControl::setWindowsBadgeTextColor(const QColor &color)
{
	d->setWindowsBadgeTextColor(color);
}

void QTaskbarControl::setProgressVisible(bool visible)
{
	if (d->progressVisible == visible)
		return;

	d->progressVisible = visible;
	d->setProgress(visible, d->progress);
	emit progressVisibleChanged(visible);
}

void QTaskbarControl::setProgress(double progress)
{
	if (qFuzzyCompare(d->progress, progress))
		return;

	d->progress = progress;
	d->setProgress(d->progressVisible, progress);
	emit progressChanged(progress);
}

void QTaskbarControl::setCounterVisible(bool visible)
{
	if (d->counterVisible == visible)
		return;

	d->counterVisible = visible;
	d->setCounter(visible, d->counter);
	emit counterVisibleChanged(visible);
}

void QTaskbarControl::setCounter(int value)
{
	if (d->counter == value)
		return;

	d->counter = value;
	d->setCounter(d->counterVisible, value);
	emit counterChanged(value);
}

bool QTaskbarControl::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::Show) {
		auto widget = qobject_cast<QWidget*>(watched);
		if (widget)
			setWindow(widget->windowHandle());
	}

	return QObject::eventFilter(watched, event);
}
