#ifndef QTASKBARCONTROL_WIN_H
#define QTASKBARCONTROL_WIN_H

#include "qtaskbarcontrol_p.h"
#include <QWinTaskbarButton>
#include <QIcon>
#include <QColor>

class QWinTaskbarControl : public QTaskbarControlPrivate
{
public:
	QWinTaskbarControl(QTaskbarControl *q_ptr);

	void setWindow(QWindow *window) override;
	bool setAttribute(QTaskbarControl::SetupKey key, const QVariant &data) override;
	QVariant attribute(QTaskbarControl::SetupKey key) override;
	void setProgress(bool progressVisible, double progress) override;
	void setCounter(bool counterVisible, int counter) override;

private:
	QTaskbarControl *_q_ptr;
	QWinTaskbarButton *_button;
	QIcon _badgeIcon {QStringLiteral(":/de/skycoder42/qtaskbarcontrol/icons/badge.png")};
	QColor _badgeColor = Qt::white;
};

#endif // QTASKBARCONTROL_WIN_H
