#include "qtaskbarcontrol_win.h"
#include <QLocale>
#include <QPainter>
#include <QWinTaskbarProgress>

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *q_ptr)
{
	return new QWinTaskbarControl(q_ptr);
}

QWinTaskbarControl::QWinTaskbarControl(QTaskbarControl *q_ptr) :
	_q_ptr(q_ptr),
	_button(new QWinTaskbarButton(q_ptr)),
	_badgeIcon(QIcon(QStringLiteral(":/de/skycoder42/qtaskbarcontrol/icons/badge.png"))),
	_badgeColor(Qt::white),
	_counterVisible(false),
	_currentBadge(),
	_currentCounter(0)
{
	updateBadge();
}

void QWinTaskbarControl::setWindow(QWindow *window)
{
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
			updateBadge();
			return true;
		} else
			return false;
	}
	case QTaskbarControl::WindowsBadgeTextColor:
		_badgeColor = data.value<QColor>();
		updateBadge();
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

void QWinTaskbarControl::setProgressVisible(bool progressVisible)
{
	_button->progress()->setVisible(progressVisible);
}

void QWinTaskbarControl::setProgress(double progress)
{
	if(progress < 0)
		_button->progress()->setRange(0, 0);
	else {
		_button->progress()->setRange(0, 1000);
		_button->progress()->setValue(progress * 1000);
	}
}

void QWinTaskbarControl::setCounterVisible(bool counterVisible)
{
	if(counterVisible) {
		_button->setOverlayIcon(_currentBadge);
		_button->setOverlayAccessibleDescription(QLocale().toString(_currentCounter));
	} else
		_button->clearOverlayIcon();
	_counterVisible = counterVisible;
}

void QWinTaskbarControl::setCounter(int counter)
{
	if(counter != _currentCounter) {
		_currentCounter = counter;
		updateBadge();
	}
}

void QWinTaskbarControl::updateBadge()
{
	_currentBadge = QIcon();
	auto text = QLocale().toString(_currentCounter);

	foreach(auto size, _badgeIcon.availableSizes()) {
		auto pm = _badgeIcon.pixmap(size);
		pm.setDevicePixelRatio(1);

		QPainter painter(&pm);
		auto font = painter.font();
		font.setPixelSize(pm.height() * 0.6);
		painter.setFont(font);
		painter.setPen(_badgeColor);
		painter.drawText(pm.rect(), Qt::AlignCenter, text);

		_currentBadge.addPixmap(pm);
	}

	if(_counterVisible) {
		_button->setOverlayIcon(_currentBadge);
		_button->setOverlayAccessibleDescription(text);
	}
}
