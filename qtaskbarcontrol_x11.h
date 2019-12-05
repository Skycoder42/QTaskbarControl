#ifndef QTASKBARCONTROL_X11_H
#define QTASKBARCONTROL_X11_H

#include "qtaskbarcontrol_p.h"

class QX11TaskbarControl : public QTaskbarControlPrivate
{
public:
	// QTaskbarControlPrivate interface
	void setProgress(bool progressVisible, double progress) override;
	void setCounter(bool counterVisible, int counter) override;

private:
	void sendMessage(const QVariantMap &params);
};

#endif // QTASKBARCONTROL_X11_H
