#include "qtaskbarcontrol_win.h"
#include <QLocale>
#include <QPainter>
#include <QWinTaskbarProgress>

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate()
{
	return new QWinTaskbarControl;
}

QWinTaskbarControl::QWinTaskbarControl() :
	_button{new QWinTaskbarButton}
{}

QWinTaskbarControl::~QWinTaskbarControl()
{
	delete _button;
}

void QWinTaskbarControl::setWindow(QWindow *window)
{
	if(_button->window() == window)
		return;

	_button->setWindow(window);
}

void QWinTaskbarControl::setWindowsProgressState(QTaskbarControl::WinProgressState state)
{
	_button->progress()->resume();
	switch (state) {
	case QTaskbarControl::Running:
	case QTaskbarControl::Paused:
		_button->progress()->pause();
		break;
	case QTaskbarControl::Stopped:
		_button->progress()->stop();
	}
}

QTaskbarControl::WinProgressState QWinTaskbarControl::windowsProgressState() const
{
	if(_button->progress()->isStopped())
		return QTaskbarControl::Stopped;

	if (_button->progress()->isPaused())
		return QTaskbarControl::Paused;

	return QTaskbarControl::Running;
}

void QWinTaskbarControl::setWindowsBadgeIcon(const QIcon &icon)
{
	if(!icon.isNull()) {
		_badgeIcon = icon;
		setCounter(_counterVisible, _counter);
	}
}

QIcon QWinTaskbarControl::windowsBadgeIcon() const
{
	return _badgeIcon;
}

void QWinTaskbarControl::setWindowsBadgeTextColor(const QColor &color)
{
	_badgeColor = color;
	setCounter(_counterVisible, _counter);
}

QColor QWinTaskbarControl::windowsBadgeTextColor() const
{
	return _badgeColor;
}

void QWinTaskbarControl::setProgress(bool progressVisible, double progress)
{
	if(progress < 0)
		_button->progress()->setRange(0, 0);
	else {
		_button->progress()->setRange(0, 1000);
		_button->progress()->setValue(static_cast<int>(progress * 1000));
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
			font.setPixelSize(static_cast<int>(pm.height() * 0.6));
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
