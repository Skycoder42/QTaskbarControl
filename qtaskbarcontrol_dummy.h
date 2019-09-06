#ifndef QTASKBARCONTROL_DUMMY_H
#define QTASKBARCONTROL_DUMMY_H

#include "qtaskbarcontrol_p.h"
#include <QVariantMap>

class QDummyTaskbarControl : public QTaskbarControlPrivate
{
public:
	// QTaskbarControlPrivate interface
	void setWindow(QWindow *window) override;
	bool setAttribute(QTaskbarControl::SetupKey key, const QVariant &data) override;
	QVariant attribute(QTaskbarControl::SetupKey key) override;
	void setProgress(bool progressVisible, double progress) override;
	void setCounter(bool counterVisible, int counter) override;
};

#endif // QTASKBARCONTROL_DUMMY_H
