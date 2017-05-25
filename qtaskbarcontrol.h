#ifndef QTASKBARCONTROL_H
#define QTASKBARCONTROL_H

#include <QVariant>
#include <QWidget>
#include <QScopedPointer>

class QTaskbarControlPrivate;
class QTaskbarControl : public QObject
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

	enum SetupKey {
		LinuxDesktopFile,

		WindowsProgressState,
		WindowsBadgeIcon,
		WindowsBadgeTextColor
	};
	Q_ENUM(SetupKey)

	explicit QTaskbarControl(QWidget *parent);
	~QTaskbarControl();

	bool setAttribute(SetupKey key, const QVariant &data);
	QVariant attribute(SetupKey key) const;

	bool progressVisible() const;
	double progress() const;
	bool counterVisible() const;
	int counter() const;

public slots:
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
	QScopedPointer<QTaskbarControlPrivate> _d;
	bool _progressVisible;
	double _progress;
	bool _counterVisible;
	int _counter;

	bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // QTASKBARCONTROL_H
