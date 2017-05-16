#ifndef QTASKBARCONTROL_X11_H
#define QTASKBARCONTROL_X11_H

#include "qtaskbarcontrol_p.h"
#include <QVariantMap>

class QX11TaskbarControl : public QTaskbarControlPrivate
{
public:
	QX11TaskbarControl();

	// QTaskbarControlPrivate interface
	void setWindow(QWindow *window) override;
	bool setAttribute(QTaskbarControl::SetupKey key, const QVariant &data) override;
	QVariant attribute(QTaskbarControl::SetupKey key) override;
	void setProgressVisible(bool progressVisible) override;
	void setProgress(double progress) override;
	void setCounterVisible(bool counterVisible) override;
	void setCounter(int counter) override;

private:
	QString _desktopFile;

	void sendMessage(QString key, QVariant value);
	void sendMessage(QVariantMap params);
	void sendReset();
};

#endif // QTASKBARCONTROL_X11_H
