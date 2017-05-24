#include "qtaskbarcontrol_mac.h"
#include <QtMacExtras>
#include <QLocale>

#import <AppKit/NSDockTile.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSImageView.h>
#import <AppKit/NSCIImageRep.h>
#import <AppKit/NSBezierPath.h>
#import <AppKit/NSColor.h>

@interface TaskProgressView : NSView {
	double _progress;
}

+ (TaskProgressView *)taskProgress;

- (void)setProgress:(double)progress;

@end

static TaskProgressView *taskProgress = nil;

@implementation TaskProgressView

+ (TaskProgressView *)taskProgress
{
	if (taskProgress == nil)
		taskProgress = [[TaskProgressView alloc] init];
	return taskProgress;
}

- (void)setProgress:(double)progress
{
	_progress = progress;
	[[NSApp dockTile] display];
}

- (void)drawRect:(NSRect)rect
{
	Q_UNUSED(rect)
	NSRect boundary = [self bounds];
	[[NSApp applicationIconImage] drawInRect:boundary
								  fromRect:NSZeroRect
								  operation:NSCompositeCopy
								  fraction:1.0];
	NSRect progressBoundary = boundary;
	progressBoundary.size.height *= 0.13;
	progressBoundary.size.width *= 0.8;
	progressBoundary.origin.x = (NSWidth(boundary) - NSWidth(progressBoundary))/2.;
	progressBoundary.origin.y = NSHeight(boundary)*0.13;

	NSRect currentProgress = progressBoundary;
	currentProgress.size.width *= _progress;
	[[NSColor blackColor] setFill];
	[NSBezierPath fillRect:progressBoundary];
	[[NSColor lightGrayColor] setFill];
	[NSBezierPath fillRect:currentProgress];
	[[NSColor blackColor] setStroke];
	[NSBezierPath strokeRect:progressBoundary];
}

@end

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *)
{
	return new QMacTaskbarControl();
}

QMacTaskbarControl::QMacTaskbarControl()
{

}

void QMacTaskbarControl::setWindow(QWindow *window)
{
	Q_UNUSED(window);
}

bool QMacTaskbarControl::setAttribute(QTaskbarControl::SetupKey key, const QVariant &data)
{
	return false;
}

QVariant QMacTaskbarControl::attribute(QTaskbarControl::SetupKey key)
{
	return QVariant();
}

void QMacTaskbarControl::setProgress(bool progressVisible, double progress)
{
	[[TaskProgressView taskProgress] setProgress:progress];
	if (progressVisible)
		[[NSApp dockTile] setContentView:[TaskProgressView taskProgress]];
	else
		[[NSApp dockTile] setContentView:nil];
	[[NSApp dockTile] display];
}

void QMacTaskbarControl::setCounter(bool counterVisible, int counter)
{
	if(counterVisible)
		QtMac::setBadgeLabelText(QLocale().toString(counter));
	else
		QtMac::setBadgeLabelText(QString());

}
