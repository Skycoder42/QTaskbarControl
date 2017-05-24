#ifndef QTASKBARCONTROL_MAC_H
#define QTASKBARCONTROL_MAC_H

#include "qtaskbarcontrol_p.h"

class QMacTaskbarControl : public QTaskbarControlPrivate
{
public:
	QMacTaskbarControl();

	void setWindow(QWindow *window) override;
	bool setAttribute(QTaskbarControl::SetupKey key, const QVariant &data) override;
	QVariant attribute(QTaskbarControl::SetupKey key) override;
	void setProgress(bool progressVisible, double progress) override;
	void setCounter(bool counterVisible, int counter) override;
};

#endif // QTASKBARCONTROL_MAC_H
