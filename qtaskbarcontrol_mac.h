#ifndef QTASKBARCONTROL_MAC_H
#define QTASKBARCONTROL_MAC_H

#include "qtaskbarcontrol_p.h"

#import <AppKit/NSView.h>

@interface TaskProgressView : NSView {
	double _progress;
}

- (void)setProgress:(double)progress;

@end

class QMacTaskbarControl : public QTaskbarControlPrivate
{
public:
	QMacTaskbarControl();
	~QMacTaskbarControl();

	void setProgress(bool progressVisible, double progress) override;
	void setCounter(bool counterVisible, int counter) override;

private:
	TaskProgressView *_taskView;
};

#endif // QTASKBARCONTROL_MAC_H
