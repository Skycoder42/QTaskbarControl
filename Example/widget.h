#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qtaskbarcontrol.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = nullptr);
	~Widget();

private slots:
	void on_progressSlider_valueChanged(int value);

private:
	Ui::Widget *ui;
	QTaskbarControl *taskbar;
};

#endif // WIDGET_H
