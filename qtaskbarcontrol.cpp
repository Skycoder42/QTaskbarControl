#include "qtaskbarcontrol.h"
#include "qtaskbarcontrol_p.h"

#include <QEvent>

QTaskbarControl::QTaskbarControl(QWidget *parent) :
	QObject(parent),
	_d(QTaskbarControlPrivate::createPrivate(this)),
	_progressVisible(false),
	_progress(0.0),
	_counterVisible(false),
	_counter(0)
{
	if(parent->windowHandle())
		_d->setWindow(parent->windowHandle());
	else
		parent->installEventFilter(this);
}

QTaskbarControl::~QTaskbarControl() = default;

bool QTaskbarControl::setAttribute(QTaskbarControl::SetupKey key, const QVariant &data)
{
	return _d->setAttribute(key, data);
}

QVariant QTaskbarControl::attribute(QTaskbarControl::SetupKey key) const
{
	return _d->attribute(key);
}

bool QTaskbarControl::progressVisible() const
{
	return _progressVisible;
}

double QTaskbarControl::progress() const
{
	return _progress;
}

bool QTaskbarControl::counterVisible() const
{
	return _counterVisible;
}

int QTaskbarControl::counter() const
{
	return _counter;
}

void QTaskbarControl::setProgressVisible(bool progressVisible)
{
	if (_progressVisible == progressVisible)
		return;

	_progressVisible = progressVisible;
	_d->setProgressVisible(progressVisible);
	emit progressVisibleChanged(progressVisible);
}

void QTaskbarControl::setProgress(double progress)
{
	if (_progress == progress)
		return;

	_progress = progress;
	_d->setProgress(progress);
	emit progressChanged(progress);
}

void QTaskbarControl::setCounterVisible(bool counterVisible)
{
	if (_counterVisible == counterVisible)
		return;

	_counterVisible = counterVisible;
	_d->setCounterVisible(counterVisible);
	emit counterVisibleChanged(counterVisible);
}

void QTaskbarControl::setCounter(int counter)
{
	if (_counter == counter)
		return;

	_counter = counter;
	_d->setCounter(counter);
	emit counterChanged(counter);
}

bool QTaskbarControl::eventFilter(QObject *watched, QEvent *event)
{
	if(watched == parent()) {
		if(event->type() == QEvent::Show) {
			auto wid = qobject_cast<QWidget*>(parent());
			if(wid)
				_d->setWindow(wid->windowHandle());
			parent()->removeEventFilter(this);
		}
	}

	return false;
}
