#ifndef QTASKBARCONTROL_X11_H
#define QTASKBARCONTROL_X11_H

#include "qtaskbarcontrol_p.h"
#include <QVariantMap>

class QX11TaskbarControl : public QTaskbarControlPrivate
{
public:
	// QTaskbarControlPrivate interface
	void setWindow(QWindow *window) override;
	bool setAttribute(QTaskbarControl::SetupKey key, const QVariant &data) override;
	QVariant attribute(QTaskbarControl::SetupKey key) override;
	void setProgress(bool progressVisible, double progress) override;
	void setCounter(bool counterVisible, int counter) override;

private:
	QString _desktopFile;

	void sendMessage(const QVariantMap &params);
	void sendReset();
};

#endif // QTASKBARCONTROL_X11_H
