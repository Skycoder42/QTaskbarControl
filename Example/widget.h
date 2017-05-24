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
	void on_progressStateComboBox_currentIndexChanged(int index);
	void on_badgeIconPushButton_clicked();
	void on_badgeTextColorPushButton_clicked();
	
	void on_indeterminatePushButton_clicked();

private:
	Ui::Widget *ui;
	QTaskbarControl *taskbar;
};

#endif // WIDGET_H
