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
	QWinTaskbarButton *_button;
};

#endif // QTASKBARCONTROL_WIN_H
