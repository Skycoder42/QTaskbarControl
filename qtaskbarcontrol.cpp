#include "qtaskbarcontrol.h"
#include "qtaskbarcontrol_p.h"

#include <QEvent>

QTaskbarControl::QTaskbarControl(QWidget *parent) :
	QObject{parent},
	d{QTaskbarControlPrivate::createPrivate(this)}
{
	Q_ASSERT_X(parent, Q_FUNC_INFO, "QTaskbarControl must have a valid parent");
	parent->installEventFilter(this);
	if(parent->windowHandle())
		d->setWindow(parent->windowHandle());
}

QTaskbarControl::~QTaskbarControl() = default;

bool QTaskbarControl::setAttribute(QTaskbarControl::SetupKey key, const QVariant &data)
{
	return d->setAttribute(key, data);
}

QVariant QTaskbarControl::attribute(QTaskbarControl::SetupKey key) const
{
	return d->attribute(key);
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
	if(watched == parent()) {
		if(event->type() == QEvent::Show) {
			auto wid = qobject_cast<QWidget*>(parent());
			if(wid)
				d->setWindow(wid->windowHandle());
		}
	}

	return false;
}
