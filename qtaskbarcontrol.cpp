#include "qtaskbarcontrol.h"
#include "qtaskbarcontrol_p.h"

#include <QEvent>
#include <QWidget>
#include <QIcon>

QTaskbarControl::QTaskbarControl(QObject *parent) :
	QObject{parent},
	d{QTaskbarControlPrivate::createPrivate()}
{}

void QTaskbarControl::setWindow(QWidget *widget)
{
	if (widget->windowHandle())
		d->setWindow(widget->windowHandle());
	else
		widget->installEventFilter(this);
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
	return d->_progressVisible;
}

double QTaskbarControl::progress() const
{
	return d->_progress;
}

bool QTaskbarControl::counterVisible() const
{
	return d->_counterVisible;
}

int QTaskbarControl::counter() const
{
	return d->_counter;
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
	if (d->_progressVisible == progressVisible)
		return;

	d->_progressVisible = progressVisible;
	d->setProgress(progressVisible, d->_progress);
	emit progressVisibleChanged(progressVisible);
}

void QTaskbarControl::setProgress(double progress)
{
	if (qFuzzyCompare(d->_progress, progress))
		return;

	d->_progress = progress;
	d->setProgress(d->_progressVisible, progress);
	emit progressChanged(progress);
}

void QTaskbarControl::setCounterVisible(bool counterVisible)
{
	if (d->_counterVisible == counterVisible)
		return;

	d->_counterVisible = counterVisible;
	d->setCounter(counterVisible, d->_counter);
	emit counterVisibleChanged(counterVisible);
}

void QTaskbarControl::setCounter(int counter)
{
	if (d->_counter == counter)
		return;

	d->_counter = counter;
	d->setCounter(d->_counterVisible, counter);
	emit counterChanged(counter);
}

bool QTaskbarControl::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::Show) {
		auto widget = qobject_cast<QWidget*>(watched);
		if (widget) {
			d->setWindow(widget->windowHandle());
			widget->removeEventFilter(this);
		}
	}

	return QObject::eventFilter(watched, event);
}
