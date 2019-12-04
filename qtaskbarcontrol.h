#ifndef QTASKBARCONTROL_H
#define QTASKBARCONTROL_H

#include <QPointer>
#include <QScopedPointer>

class QWindow;
class QTaskbarControlPrivate;

class Q_TASKBAR_CONTROL_EXPORT QTaskbarControl : public QObject
{
	Q_OBJECT

	Q_PROPERTY(bool progressVisible READ progressVisible WRITE setProgressVisible NOTIFY progressVisibleChanged)
	Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
	Q_PROPERTY(bool counterVisible READ counterVisible WRITE setCounterVisible NOTIFY counterVisibleChanged)
	Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged)

public:
	enum WinProgressState {
		Running,
		Paused,
		Stopped
	};
	Q_ENUM(WinProgressState)

	explicit QTaskbarControl(QObject *parent);
	~QTaskbarControl() override;

	void setWidget(QWidget *widget);
	void setWindow(QWindow *window);
	WinProgressState windowsProgressState() const;
	QIcon windowsBadgeIcon() const;
	QColor windowsBadgeTextColor() const;
	bool progressVisible() const;
	double progress() const;
	bool counterVisible() const;
	int counter() const;

public slots:
	void setWindowsProgressState(WinProgressState state);
	void setWindowsBadgeIcon(const QIcon &icon);
	void setWindowsBadgeTextColor(const QColor &color);
	void setProgressVisible(bool progressVisible);
	void setProgress(double progress);
	void setCounterVisible(bool counterVisible);
	void setCounter(int counter);

signals:
	void progressVisibleChanged(bool progressVisible);
	void progressChanged(double progress);
	void counterVisibleChanged(bool counterVisible);
	void counterChanged(int counter);

private:
	QScopedPointer<QTaskbarControlPrivate> d;
	QPointer<QWidget> _watchedWidget;

	bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // QTASKBARCONTROL_H
