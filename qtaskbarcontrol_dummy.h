#ifndef QTASKBARCONTROL_DUMMY_H
#define QTASKBARCONTROL_DUMMY_H

#include "qtaskbarcontrol_p.h"

class QDummyTaskbarControl : public QTaskbarControlPrivate
{
public:
	// QTaskbarControlPrivate interface
	void setProgress(bool visible, double value) override;
	void setCounter(bool visible, int value) override;
};

#endif // QTASKBARCONTROL_DUMMY_H
