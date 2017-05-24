#include "qtaskbarcontrol_x11.h"
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *)
{
	return new QX11TaskbarControl();
}

QX11TaskbarControl::QX11TaskbarControl() :
	_desktopFile()
{}

void QX11TaskbarControl::setWindow(QWindow *window)
{
	Q_UNUSED(window);
}

bool QX11TaskbarControl::setAttribute(QTaskbarControl::SetupKey key, const QVariant &data)
{
	switch (key) {
	case QTaskbarControl::LinuxDesktopFile:
		if(!_desktopFile.isEmpty())
			sendReset();
		_desktopFile = data.toString();
		sendReset();
		return true;
	default:
		return false;
	}
}

QVariant QX11TaskbarControl::attribute(QTaskbarControl::SetupKey key)
{
	switch (key) {
	case QTaskbarControl::LinuxDesktopFile:
		return _desktopFile;
	default:
		return QVariant();
	}
}

void QX11TaskbarControl::setProgressVisible(bool progressVisible)
{
	sendMessage(QStringLiteral("progress-visible"), progressVisible);
}

void QX11TaskbarControl::setProgress(double progress)
{
	sendMessage(QStringLiteral("progress"), progress);
}

void QX11TaskbarControl::setCounterVisible(bool counterVisible)
{
	sendMessage(QStringLiteral("count-visible"), counterVisible);
}

void QX11TaskbarControl::setCounter(int counter)
{
	sendMessage(QStringLiteral("count"), counter);
}

void QX11TaskbarControl::sendMessage(QString key, QVariant value)
{
	QVariantMap properties;
	properties.insert(key, value);
	sendMessage(properties);
}

void QX11TaskbarControl::sendMessage(QVariantMap params)
{
	if(_desktopFile.isEmpty()) {
		qWarning() << "You need to set the" << QTaskbarControl::LinuxDesktopFile << "attribute before you can use QTaskbarControl!";
		return;
	}

	auto message = QDBusMessage::createSignal(QStringLiteral("/de/skycoder42/QTaskbarProgress"),
											  QStringLiteral("com.canonical.Unity.LauncherEntry"),
											  QStringLiteral("Update"));

	message << QStringLiteral("application://") + _desktopFile
			<< params;
	QDBusConnection::sessionBus().send(message);
}

void QX11TaskbarControl::sendReset()
{
	QVariantMap properties;
	properties.insert(QStringLiteral("progress-visible"), false);
	properties.insert(QStringLiteral("progress"), 0.0);
	properties.insert(QStringLiteral("count-visible"), false);
	properties.insert(QStringLiteral("count"), 0);
	sendMessage(properties);

}
