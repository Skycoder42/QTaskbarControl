#ifndef QTASKBARCONTROL_WIN_H
#define QTASKBARCONTROL_WIN_H

#include "qtaskbarcontrol_p.h"
#include <QWinTaskbarButton>

class QWinTaskbarControl : public QTaskbarControlPrivate
{
public:
	QWinTaskbarControl(QTaskbarControl *q_ptr);

	void setWindow(QWindow *window) override;
	bool setAttribute(QTaskbarControl::SetupKey key, const QVariant &data) override;
	QVariant attribute(QTaskbarControl::SetupKey key) override;
	void setProgressVisible(bool progressVisible) override;
	void setProgress(double progress) override;
	void setCounterVisible(bool counterVisible) override;
	void setCounter(int counter) override;

private:
	QTaskbarControl *_q_ptr;
	QWinTaskbarButton *_button;
	QIcon _badgeIcon;
	QColor _badgeColor;

	bool _counterVisible;
	QIcon _currentBadge;
	int _currentCounter;

	void updateBadge();
};

#endif // QTASKBARCONTROL_WIN_H
