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

	if (_watchedWidget)
		_watchedWidget->removeEventFilter(this);

	_watchedWidget = widget;

	if (_watchedWidget)
		_watchedWidget->installEventFilter(this);
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

void QTaskbarControl::setProgressVisible(bool progressVisible)
{
	if (d->progressVisible == progressVisible)
		return;

	d->progressVisible = progressVisible;
	d->setProgress(progressVisible, d->progress);
	emit progressVisibleChanged(progressVisible);
}

void QTaskbarControl::setProgress(double progress)
{
	if (qFuzzyCompare(d->progress, progress))
		return;

	d->progress = progress;
	d->setProgress(d->progressVisible, progress);
	emit progressChanged(progress);
}

void QTaskbarControl::setCounterVisible(bool counterVisible)
{
	if (d->counterVisible == counterVisible)
		return;

	d->counterVisible = counterVisible;
	d->setCounter(counterVisible, d->counter);
	emit counterVisibleChanged(counterVisible);
}

void QTaskbarControl::setCounter(int counter)
{
	if (d->counter == counter)
		return;

	d->counter = counter;
	d->setCounter(d->counterVisible, counter);
	emit counterChanged(counter);
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
