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
	void setWindowsProgressState(QTaskbarControl::WinProgressState state) override;
	QTaskbarControl::WinProgressState windowsProgressState() const override;
	void setWindowsBadgeIcon(const QIcon &icon) override;
	QIcon windowsBadgeIcon() const override;
	void setWindowsBadgeTextColor(const QColor &color) override;
	QColor windowsBadgeTextColor() const override;
	void setProgress(bool visible, double progress) override;
	void setCounter(bool visible, int counter) override;

private:
	QTaskbarControl *_q_ptr;
	QWinTaskbarButton *_button;
	QIcon _badgeIcon {QStringLiteral(":/de/skycoder42/qtaskbarcontrol/icons/badge.png")};
	QColor _badgeColor = Qt::white;
};

#endif // QTASKBARCONTROL_WIN_H
