#include "qtaskbarcontrol_dummy.h"

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *)
{
	return new QDummyTaskbarControl{};
}

void QDummyTaskbarControl::setProgress(bool visible, double value)
{
	Q_UNUSED(visible)
	Q_UNUSED(value)
}

void QDummyTaskbarControl::setCounter(bool visible, int value)
{
	Q_UNUSED(visible)
	Q_UNUSED(value)
}
