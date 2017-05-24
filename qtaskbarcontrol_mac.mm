#include "qtaskbarcontrol_mac.h"
#include <QtMacExtras>
#include <QLocale>

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *)
{
	return new QMacTaskbarControl();
}

QMacTaskbarControl::QMacTaskbarControl()
{

}

void QMacTaskbarControl::setWindow(QWindow *window)
{
	Q_UNUSED(window);
}

bool QMacTaskbarControl::setAttribute(QTaskbarControl::SetupKey key, const QVariant &data)
{
	return false;
}

QVariant QMacTaskbarControl::attribute(QTaskbarControl::SetupKey key)
{
	return QVariant();
}

void QMacTaskbarControl::setProgress(bool progressVisible, double progress)
{
}

void QMacTaskbarControl::setCounter(bool counterVisible, int counter)
{
	if(counterVisible)
		QtMac::setBadgeLabelText(QLocale().toString(counter));
	else
		QtMac::setBadgeLabelText(QString());

}
