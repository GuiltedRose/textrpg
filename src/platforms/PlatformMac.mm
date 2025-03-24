// PlatformWindowMac.mm
#import <Cocoa/Cocoa.h>
#include "platforms/PlatformMac.h"
#include <string>
#include <thread>
#include <chrono>

static NSTextView* textView = nil;
static std::string inputBuffer;
static bool lineReady = false;

// === Custom TextView to Capture Key Presses ===

@interface RPGInputTextView : NSTextView
@end

@implementation RPGInputTextView
- (void)keyDown:(NSEvent *)event {
    NSString *chars = [event characters];
    if ([chars length] == 0) return;

    unichar ch = [chars characterAtIndex:0];
    if (ch == NSCarriageReturnCharacter || ch == '\n') {
        lineReady = true;
    } else if (ch == NSDeleteCharacter || ch == 127) {
        if (!inputBuffer.empty()) inputBuffer.pop_back();
    } else if (isprint(ch)) {
        inputBuffer += static_cast<char>(ch);
    }

    [super keyDown:event];
}
@end

// === Window Delegate ===

@interface RPGWindowDelegate : NSObject <NSApplicationDelegate>
@end

@implementation RPGWindowDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    NSRect frame = NSMakeRect(100, 100, 640, 480);
    NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;

    NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:style
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
    [window setTitle:@"TextRPG"];

    NSScrollView *scrollView = [[NSScrollView alloc] initWithFrame:[[window contentView] bounds]];
    [scrollView setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];

    textView = [[RPGInputTextView alloc] initWithFrame:[[window contentView] bounds]];
    [textView setEditable:NO];
    [textView setSelectable:NO];
    [textView setFont:[NSFont userFixedPitchFontOfSize:14]];

    [scrollView setDocumentView:textView];
    [[window contentView] addSubview:scrollView];

    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}
@end

// === PlatformWindowMac C++ Implementation ===

PlatformWindowMac::PlatformWindowMac() {
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    RPGWindowDelegate *delegate = [[RPGWindowDelegate alloc] init];
    [NSApp setDelegate:delegate];
}

PlatformWindowMac::~PlatformWindowMac() {}

void PlatformWindowMac::createWindow() {
    [NSApp finishLaunching];
}

void PlatformWindowMac::clear() {
    [[textView textStorage] setAttributedString:[[NSAttributedString alloc] initWithString:@""]];
}

void PlatformWindowMac::drawText(const std::string& text) {
    NSString *nsText = [NSString stringWithUTF8String:text.c_str()];
    NSTextStorage *storage = [textView textStorage];
    NSAttributedString *attr = [[NSAttributedString alloc] initWithString:[nsText stringByAppendingString:@"\n"]];
    [storage appendAttributedString:attr];
    [textView scrollRangeToVisible:NSMakeRange([[textView string] length], 0)];
}

void PlatformWindowMac::refresh() {
    // Cocoa auto-refreshes
}

void PlatformWindowMac::setWriteMode(bool enabled) {
    // Optional
}

char PlatformWindowMac::waitForCharInput() {
    while (!lineReady && inputBuffer.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    char ch = inputBuffer.front();
    inputBuffer.erase(0, 1);
    return ch;
}

std::string PlatformWindowMac::waitForLineInput() {
    inputBuffer.clear();
    lineReady = false;

    while (!lineReady) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    lineReady = false;
    return inputBuffer;
}

void PlatformWindowMac::run() {
    [NSApp run];
}
