#include "widget.h"
#include "ui_widget.h"
#ifdef Q_OS_LINUX
#include <QUuid>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#endif

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget),
	taskbar(new QTaskbarControl(this))
{
	ui->setupUi(this);

	connect(ui->progressCheckBox, &QCheckBox::clicked,
			taskbar, &QTaskbarControl::setProgressVisible);
	connect(ui->counterCheckBox, &QCheckBox::clicked,
			taskbar, &QTaskbarControl::setCounterVisible);
	connect(ui->counterSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
			taskbar, &QTaskbarControl::setCounter);

#ifdef Q_OS_LINUX
	auto name = QUuid::createUuid().toString() + QStringLiteral(".desktop");
	QDir appDir = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
	QFile desktopFile(appDir.absoluteFilePath(name));
	if(!desktopFile.exists()) {
		desktopFile.open(QIODevice::WriteOnly);
		desktopFile.write("[Desktop Entry]\n");
		desktopFile.write("Type=Application\n");
		desktopFile.write("Version=1.1\n");
		desktopFile.write("Name=" + QApplication::applicationDisplayName().toUtf8() + "\n");
		desktopFile.write("Exec=" + QApplication::applicationFilePath().toUtf8() + "\n");
		desktopFile.close();
	}
	taskbar->setAttribute(QTaskbarControl::LinuxDesktopFile, name);
	ui->desktopFileLineEdit->setText(name);
#else
	ui->desktopFileLabel->setVisible(false);
	ui->desktopFileLineEdit->setVisible(false);
#endif
}

Widget::~Widget()
{
#ifdef Q_OS_LINUX
	auto name = taskbar->attribute(QTaskbarControl::LinuxDesktopFile).toString();
	QDir appDir = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
	QFile::remove(appDir.absoluteFilePath(name));
#endif

	delete ui;
}

void Widget::on_progressSlider_valueChanged(int value)
{
	taskbar->setProgress(value/(double)ui->progressSlider->maximum());
}
