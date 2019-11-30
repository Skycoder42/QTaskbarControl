#include "qtaskbarcontrol_dummy.h"

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *)
{
	return new QDummyTaskbarControl{};
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
