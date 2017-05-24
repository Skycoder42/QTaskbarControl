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
	progressRect.origin.y = 1;

	auto radius = progressRect.size.height / 2.0;

	NSRect currentRect = progressRect;
	currentRect.size.width = (currentRect.size.width - 2*radius) * _progress + 2*radius;

	auto cBase = 0xce / 256.0f;
	NSColor *baseColor = [NSColor colorWithRed:cBase green:cBase blue:cBase alpha:1.0f];
	auto cFill = 0x4f / 256.0f;
	NSColor *fillColor = [NSColor colorWithRed:cFill green:cFill blue:cFill alpha:1.0f];

	NSBezierPath *basePath = [NSBezierPath bezierPath];
	[basePath appendBezierPathWithRoundedRect:progressRect xRadius:radius yRadius:radius];
	[baseColor setFill];
	[basePath fill];

	NSBezierPath *progressPath = [NSBezierPath bezierPath];
	[progressPath appendBezierPathWithRoundedRect:currentRect xRadius:radius yRadius:radius];
	[fillColor setFill];
	[progressPath fill];

	NSBezierPath *framePath = [NSBezierPath bezierPath];
	[framePath appendBezierPathWithRoundedRect:progressRect xRadius:radius yRadius:radius];
	[fillColor setStroke];
	[framePath stroke];
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
