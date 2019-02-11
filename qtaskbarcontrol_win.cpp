#include "qtaskbarcontrol_win.h"
#include <QLocale>
#include <QPainter>
#include <QWinTaskbarProgress>

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *q_ptr)
{
	return new QWinTaskbarControl{q_ptr};
}

QWinTaskbarControl::QWinTaskbarControl(QTaskbarControl *q_ptr) :
	_q_ptr{q_ptr},
	_button{new QWinTaskbarButton{q_ptr}}
{}

void QWinTaskbarControl::setWindow(QWindow *window)
{
	if(_button->window() == window)
		return;

	_button->setWindow(window);
}

bool QWinTaskbarControl::setAttribute(QTaskbarControl::SetupKey key, const QVariant &data)
{
	switch (key) {
	case QTaskbarControl::WindowsProgressState:
		_button->progress()->resume();
		switch (data.toInt()) {
		case QTaskbarControl::Running:
			return true;
		case QTaskbarControl::Paused:
			_button->progress()->pause();
			return true;
		case QTaskbarControl::Stopped:
			_button->progress()->stop();
			return true;
		default:
			return false;
		}
	case QTaskbarControl::WindowsBadgeIcon:
	{
		auto icon = data.value<QIcon>();
		if(!icon.isNull()) {
			_badgeIcon = icon;
			setCounter(_q_ptr->counterVisible(), _q_ptr->counter());
			return true;
		} else
			return false;
	}
	case QTaskbarControl::WindowsBadgeTextColor:
		_badgeColor = data.value<QColor>();
		setCounter(_q_ptr->counterVisible(), _q_ptr->counter());
	default:
		return false;
	}
}

QVariant QWinTaskbarControl::attribute(QTaskbarControl::SetupKey key)
{
	switch (key) {
	case QTaskbarControl::WindowsProgressState:
		if(_button->progress()->isStopped())
			return QTaskbarControl::Stopped;
		else if (_button->progress()->isPaused())
			return QTaskbarControl::Paused;
		else
			return QTaskbarControl::Running;

	case QTaskbarControl::WindowsBadgeIcon:
		return QVariant::fromValue(_badgeIcon);
	case QTaskbarControl::WindowsBadgeTextColor:
		return _badgeColor;
	default:
		return QVariant();
	}
}

void QWinTaskbarControl::setProgress(bool progressVisible, double progress)
{
	if(progress < 0)
		_button->progress()->setRange(0, 0);
	else {
		_button->progress()->setRange(0, 1000);
		_button->progress()->setValue(progress * 1000);
	}
	_button->progress()->setVisible(progressVisible);
}

void QWinTaskbarControl::setCounter(bool counterVisible, int counter)
{
	if(counterVisible) {
		QIcon currentBadge;
		auto text = QLocale{}.toString(counter);

		foreach(auto size, _badgeIcon.availableSizes()) {
			auto pm = _badgeIcon.pixmap(size);
			pm.setDevicePixelRatio(1);

			QPainter painter{&pm};
			auto font = painter.font();
			font.setPixelSize(pm.height() * 0.6);
			painter.setFont(font);
			painter.setPen(_badgeColor);
			painter.drawText(pm.rect(), Qt::AlignCenter, text);

			currentBadge.addPixmap(pm);
		}

		_button->setOverlayIcon(currentBadge);
		_button->setOverlayAccessibleDescription(text);
	} else
		_button->clearOverlayIcon();
}
