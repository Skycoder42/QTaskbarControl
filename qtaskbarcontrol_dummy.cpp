#include "qtaskbarcontrol_dummy.h"

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *)
{
	return new QDummyTaskbarControl{};
}

void QDummyTaskbarControl::setWindow(QWindow *window)
{
	Q_UNUSED(window);
}

bool QDummyTaskbarControl::setAttribute(QTaskbarControl::SetupKey key, const QVariant &data)
{
	Q_UNUSED(key)
	Q_UNUSED(data)
	return false;
}

QVariant QDummyTaskbarControl::attribute(QTaskbarControl::SetupKey key)
{
	Q_UNUSED(key)
	return {};
}

void QDummyTaskbarControl::setProgress(bool progressVisible, double progress)
{
	Q_UNUSED(progressVisible)
	Q_UNUSED(progress)
}

void QDummyTaskbarControl::setCounter(bool counterVisible, int counter)
{
	Q_UNUSED(counterVisible)
	Q_UNUSED(counter)
}
