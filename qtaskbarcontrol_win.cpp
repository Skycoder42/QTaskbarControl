#include "qtaskbarcontrol_win.h"
#include <QWinTaskbarProgress>

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *q_ptr)
{
	return new QWinTaskbarControl(q_ptr);
}

QWinTaskbarControl::QWinTaskbarControl(QTaskbarControl *q_ptr) :
	_button(new QWinTaskbarButton(q_ptr))
{
	_button->progress()->setRange(0, 1000);
}

void QWinTaskbarControl::setWindow(QWindow *window)
{
	_button->setWindow(window);
}

bool QWinTaskbarControl::setAttribute(QTaskbarControl::SetupKey key, const QVariant &data)
{
	return false;
}

QVariant QWinTaskbarControl::attribute(QTaskbarControl::SetupKey key)
{
	return QVariant();
}

void QWinTaskbarControl::setProgressVisible(bool progressVisible)
{
	_button->progress()->setVisible(progressVisible);
}

void QWinTaskbarControl::setProgress(double progress)
{
	_button->progress()->setValue(progress * 1000);
}

void QWinTaskbarControl::setCounterVisible(bool counterVisible)
{
}

void QWinTaskbarControl::setCounter(int counter)
{
}
