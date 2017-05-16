#ifndef QTASKBARCONTROL_H
#define QTASKBARCONTROL_H

#include <QObject>

class QTaskbarControl : public QObject
{
	Q_OBJECT
public:
	explicit QTaskbarControl(QObject *parent = 0);

signals:

public slots:
};

#endif // QTASKBARCONTROL_H