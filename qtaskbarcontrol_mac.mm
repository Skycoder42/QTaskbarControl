#include "qtaskbarcontrol_mac.h"
#include <QtMacExtras>
#include <QLocale>

#import <AppKit/NSApplication.h>
#import <AppKit/NSImageView.h>
#import <AppKit/NSDockTile.h>
#import <AppKit/NSColor.h>
#import <AppKit/NSCIImageRep.h>
#import <AppKit/NSBezierPath.h>

@implementation TaskProgressView

- (void)setProgress:(double)progress
{
	_progress = progress;
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
	progressRect.size.height *= 0.042;
	progressRect.origin.x = (NSWidth(bounds) - NSWidth(progressRect)) / 2.0;
	progressRect.origin.y = 0;

	NSRect currentRect = progressRect;
	currentRect.size.width *= _progress;

	auto d1 = 0xce / 256.0f;
	auto d2 = 0x4f / 256.0f;

	[[NSColor colorWithRed:d1 green:d1 blue:d1 alpha:1.0f] setFill];
	[NSBezierPath fillRect:progressRect];

	[[NSColor colorWithRed:d2 green:d2 blue:d2 alpha:1.0f] setFill];
	[NSBezierPath fillRect:currentRect];

	[[NSColor colorWithRed:d2 green:d2 blue:d2 alpha:1.0f] setStroke];
	[NSBezierPath strokeRect:progressRect];
}

@end

QTaskbarControlPrivate *QTaskbarControlPrivate::createPrivate(QTaskbarControl *)
{
	return new QMacTaskbarControl();
}

QMacTaskbarControl::QMacTaskbarControl() :
	_taskView([[TaskProgressView alloc] init])
{}

QMacTaskbarControl::~QMacTaskbarControl()
{
	[_taskView release];
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
	[_taskView setProgress:progress];
	if (progressVisible)
		[[NSApp dockTile] setContentView:_taskView];
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
