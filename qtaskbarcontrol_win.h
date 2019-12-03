#ifndef QTASKBARCONTROL_WIN_H
#define QTASKBARCONTROL_WIN_H

#include "qtaskbarcontrol_p.h"
#include <QWinTaskbarButton>
#include <QIcon>
#include <QColor>

class QWinTaskbarControl : public QTaskbarControlPrivate
{
public:
	QWinTaskbarControl();
	~QWinTaskbarControl() override;

	void setWindow(QWindow *window) override;
	void setWindowsProgressState(QTaskbarControl::WinProgressState state) override;
	QTaskbarControl::WinProgressState windowsProgressState() const override;
	void setWindowsBadgeIcon(const QIcon &icon) override;
	QIcon windowsBadgeIcon() const override;
	void setWindowsBadgeTextColor(const QColor &color) override;
	QColor windowsBadgeTextColor() const override;
	void setProgress(bool progressVisible, double progress) override;
	void setCounter(bool counterVisible, int counter) override;

private:
	QWinTaskbarButton *_button;
	QIcon _badgeIcon {QStringLiteral(":/de/skycoder42/qtaskbarcontrol/icons/badge.png")};
	QColor _badgeColor = Qt::white;
};

#endif // QTASKBARCONTROL_WIN_H
