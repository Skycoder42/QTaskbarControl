#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QColorDialog>
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
	QGuiApplication::setDesktopFileName(name);
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
	ui->desktopFileLineEdit->setText(name);
#else
	ui->desktopFileLabel->setVisible(false);
	ui->desktopFileLineEdit->setVisible(false);
#endif
#ifndef Q_OS_WIN
	ui->progressStateLabel->setVisible(false);
	ui->progressStateComboBox->setVisible(false);
	ui->badgeIconLabel->setVisible(false);
	ui->badgeIconPushButton->setVisible(false);
	ui->badgeTextColorLabel->setVisible(false);
	ui->badgeTextColorPushButton->setVisible(false);
	ui->indeterminateLabel->setVisible(false);
	ui->indeterminatePushButton->setVisible(false);
#endif
}

Widget::~Widget()
{
#ifdef Q_OS_LINUX
	auto name = QGuiApplication::desktopFileName();
	QDir appDir = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
	QFile::remove(appDir.absoluteFilePath(name));
#endif

	delete ui;
}

void Widget::on_progressSlider_valueChanged(int value)
{
	taskbar->setProgress(value/(double)ui->progressSlider->maximum());
}

void Widget::on_progressStateComboBox_currentIndexChanged(int index)
{
	taskbar->setWindowsProgressState((QTaskbarControl::WinProgressState)index);
}

void Widget::on_badgeIconPushButton_clicked()
{
	auto file = QFileDialog::getOpenFileName(this,
											 tr("Select an icon"),
											 QString(),
											 tr("Icons (*.ico *.png *.bmp);;All Files (*)"));
	if(!file.isNull())
		taskbar->setWindowsBadgeIcon(QIcon(file));
}

void Widget::on_badgeTextColorPushButton_clicked()
{
	auto color = QColorDialog::getColor(taskbar->windowsBadgeTextColor(),
										this,
										tr("Select a color"));
	if(color.isValid())
		taskbar->setWindowsBadgeTextColor(color);
}

void Widget::on_indeterminatePushButton_clicked()
{
	taskbar->setProgress(-1);
}
