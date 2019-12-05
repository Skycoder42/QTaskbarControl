#ifndef QTASKBARCONTROL_DUMMY_H
#define QTASKBARCONTROL_DUMMY_H

#include "qtaskbarcontrol_p.h"

class QDummyTaskbarControl : public QTaskbarControlPrivate
{
public:
	// QTaskbarControlPrivate interface
	void setProgress(bool progressVisible, double progress) override;
	void setCounter(bool counterVisible, int counter) override;
};

#endif // QTASKBARCONTROL_DUMMY_H
