#include "widget.h"
#include "ui_widget.h"

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
	//TODO create desktop file
#endif
}

Widget::~Widget()
{
#ifdef Q_OS_LINUX
	//TODO delete desktop file
#endif

	delete ui;
}

void Widget::on_progressSlider_valueChanged(int value)
{
	taskbar->setProgress(value/(double)ui->progressSlider->maximum());
}
