#ifndef QTASKBARCONTROL_X11_H
#define QTASKBARCONTROL_X11_H

#include "qtaskbarcontrol_p.h"

class QX11TaskbarControl : public QTaskbarControlPrivate
{
public:
	// QTaskbarControlPrivate interface
	void setProgress(bool visible, double value) override;
	void setCounter(bool visible, int value) override;

private:
	void sendMessage(const QVariantMap &params);
};

#endif // QTASKBARCONTROL_X11_H
