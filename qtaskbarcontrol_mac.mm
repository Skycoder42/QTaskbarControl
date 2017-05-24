#include "qtaskbarcontrol_mac.h"
#include <QtMacExtras>
#include <QLocale>

#import <AppKit/NSApplication.h>
#import <AppKit/NSImageView.h>
#import <AppKit/NSDockTile.h>
#import <AppKit/NSColor.h>
#import <AppKit/NSCIImageRep.h>
#import <AppKit/NSBezierPath.h>

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
	NSRect bounds = [self bounds];
	[[NSApp applicationIconImage] drawInRect:bounds
								  fromRect:NSZeroRect
								  operation:NSCompositeCopy
								  fraction:1.0];
	NSRect progressRect = bounds;
	progressRect.size.width *= 0.8;
	progressRect.size.height *= 0.125;
	progressRect.origin.x = (NSWidth(bounds) - NSWidth(progressRect)) / 2.0;
	progressRect.origin.y = NSHeight(bounds) * 0.25;

	NSRect currentRect = progressRect;
	currentRect.size.width *= _progress;

	[[NSColor darkGrayColor] setFill];
	[NSBezierPath fillRect:progressRect];

	[[NSColor lightGrayColor] setFill];
	[NSBezierPath fillRect:currentRect];

	[[NSColor darkGrayColor] setStroke];
	[NSBezierPath strokeRect:progressRect];
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
