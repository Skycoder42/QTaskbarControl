#ifndef QTASKBARCONTROL_P_H
#define QTASKBARCONTROL_P_H

#include "qtaskbarcontrol.h"

class QWindow;

class QTaskbarControlPrivate
{
	Q_DISABLE_COPY(QTaskbarControlPrivate)
	friend class QTaskbarControl;

public:
	static QTaskbarControlPrivate *createPrivate();

	QTaskbarControlPrivate() = default;
	virtual ~QTaskbarControlPrivate() = default;

	virtual void setWindow(QWindow *window);
	virtual void setWindowsProgressState(QTaskbarControl::WinProgressState state);
	virtual QTaskbarControl::WinProgressState windowsProgressState() const;
	virtual void setWindowsBadgeIcon(const QIcon &icon);
	virtual QIcon windowsBadgeIcon() const;
	virtual void setWindowsBadgeTextColor(const QColor &color);
	virtual QColor windowsBadgeTextColor() const;
	virtual void setProgress(bool progressVisible, double progress) = 0;
	virtual void setCounter(bool counterVisible, int counter) = 0;

protected:
	bool _progressVisible;
	double _progress;
	bool _counterVisible;
	int _counter;
};

#endif // QTASKBARCONTROL_P_H
