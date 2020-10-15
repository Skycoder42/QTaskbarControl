#ifndef QTASKBARCONTROL_P_H
#define QTASKBARCONTROL_P_H

#include "qtaskbarcontrol.h"

class QWindow;

class QTaskbarControlPrivate
{
	Q_DISABLE_COPY(QTaskbarControlPrivate)
	friend class QTaskbarControl;

public:
	static QTaskbarControlPrivate *createPrivate(QTaskbarControl *q_ptr);

	QTaskbarControlPrivate() = default;
	virtual ~QTaskbarControlPrivate() = default;

	virtual void setWindow(QWindow *window);
	virtual void setWindowsProgressState(QTaskbarControl::WinProgressState state);
	virtual QTaskbarControl::WinProgressState windowsProgressState() const;
	virtual void setWindowsBadgeIcon(const QIcon &icon);
	virtual QIcon windowsBadgeIcon() const;
	virtual void setWindowsBadgeTextColor(const QColor &color);
	virtual QColor windowsBadgeTextColor() const;
	virtual void setProgress(bool visible, double value) = 0;
	virtual void setCounter(bool visible, int value) = 0;

private:
	QPointer<QWidget> watchedWidget;
	bool progressVisible;
	double progress;
	bool counterVisible;
	int counter;
};

#endif // QTASKBARCONTROL_P_H
