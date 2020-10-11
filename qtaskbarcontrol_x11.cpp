#include "qtaskbarcontrol_x11.h"
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>
#include <QGuiApplication>

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *)
{
	return new QX11TaskbarControl{};
}

void QX11TaskbarControl::setProgress(bool visible, double progress)
{
	QVariantMap properties;
	properties.insert(QStringLiteral("progress-visible"), visible);
	properties.insert(QStringLiteral("progress"), progress);
	sendMessage(properties);
}

void QX11TaskbarControl::setCounter(bool visible, int value)
{
	QVariantMap properties;
	properties.insert(QStringLiteral("count-visible"), visible);
	properties.insert(QStringLiteral("count"), value);
	sendMessage(properties);
}

void QX11TaskbarControl::sendMessage(const QVariantMap &params)
{
	if(QGuiApplication::desktopFileName().isEmpty()) {
		qWarning() << "You need to set the desktop file name before you can use QTaskbarControl!";
		return;
	}

	auto message = QDBusMessage::createSignal(QStringLiteral("/de/skycoder42/QTaskbarProgress"),
											  QStringLiteral("com.canonical.Unity.LauncherEntry"),
											  QStringLiteral("Update"));

	message << QStringLiteral("application://") + QGuiApplication::desktopFileName()
			<< params;
	QDBusConnection::sessionBus().send(message);
}
