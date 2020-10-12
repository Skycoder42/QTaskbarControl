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

- (void)setProgress:(double)value
{
	_progress = value;
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
	return new QMacTaskbarControl{};
}

QMacTaskbarControl::QMacTaskbarControl() :
	_taskView{[[TaskProgressView alloc] init]}
{}

QMacTaskbarControl::~QMacTaskbarControl()
{
	[_taskView release];
}

void QMacTaskbarControl::setProgress(bool visible, double value)
{
	[_taskView setProgress:value];
	if (visible && value >= 0.0)
		[[NSApp dockTile] setContentView:_taskView];
	else
		[[NSApp dockTile] setContentView:nil];
	[[NSApp dockTile] display];
}

void QMacTaskbarControl::setCounter(bool visible, int value)
{
	if(visible)
		QtMac::setBadgeLabelText(QLocale().toString(value));
	else
		QtMac::setBadgeLabelText(QString());
}
