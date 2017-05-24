#ifndef QTASKBARCONTROL_P_H
#define QTASKBARCONTROL_P_H

#include "qtaskbarcontrol.h"

class QTaskbarControlPrivate
{
public:
	static QTaskbarControlPrivate *createPrivate(QTaskbarControl *q_ptr);

	virtual ~QTaskbarControlPrivate() = default;

	virtual void setWindow(QWindow *window) = 0;
	virtual bool setAttribute(QTaskbarControl::SetupKey key, const QVariant &data) = 0;
	virtual QVariant attribute(QTaskbarControl::SetupKey key) = 0;
	virtual void setProgress(bool progressVisible, double progress) = 0;
	virtual void setCounter(bool counterVisible, int counter) = 0;
};

#endif // QTASKBARCONTROL_P_H
