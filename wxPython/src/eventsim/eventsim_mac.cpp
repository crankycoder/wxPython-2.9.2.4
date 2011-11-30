/*
Copyright 2008 Kevin Ollivier
Licensed under the wxWidgets license
*/    

#include "UIEventSimulator.h"

#include <wx/defs.h>

#ifdef __WXMAC__

#include <ApplicationServices/ApplicationServices.h>

CGEventTapLocation tap = kCGSessionEventTap;

CGEventType CGEventTypeForMouseButton(int button, bool isDown)
{
    switch (button)
    {
        case wxMOUSE_BTN_LEFT:
            if (isDown)
                return kCGEventLeftMouseDown;
            else
                return kCGEventLeftMouseUp;
        case wxMOUSE_BTN_RIGHT:
            if (isDown)
                return kCGEventRightMouseDown;
            else
                return kCGEventRightMouseUp;
                
        // Apparently all other buttons use the constant OtherMouseDown 
            
        default:
            if (isDown)
                return kCGEventOtherMouseDown;
            else
                return kCGEventOtherMouseUp;
    }
}

void SendCharCode(CGCharCode keycode, bool isDown)
{
    CGEventRef event = CGEventCreateKeyboardEvent(NULL, keycode, isDown);
    if (event)
    {
        CGEventPost(kCGHIDEventTap, event);
    }
    CFRelease(event);
}

bool UIEventSimulator::MouseDown(int button)
{
    CGPoint pos;
    int x, y;
    wxGetMousePosition(&x, &y); 
    pos.x = x;
    pos.y = y;
    CGEventType type = CGEventTypeForMouseButton(button, true);
    CGEventRef event = CGEventCreateMouseEvent(NULL, type, pos, button);
    CGEventSetType(event, type);
    
    if (event)
    {
        CGEventPost(tap, event);
    }
    CFRelease(event);
    return true;
}

bool UIEventSimulator::MouseMove(long x, long y)
{
    CGPoint pos;
    pos.x = x;
    pos.y = y;
    CGEventType type = kCGEventMouseMoved;
    CGEventRef event = CGEventCreateMouseEvent(NULL, type, pos, kCGMouseButtonLeft);
    CGEventSetType(event, type);
    
    if (event)
    {
        CGEventPost(tap, event);
    }
    CFRelease(event);
    
    return true;
}

bool UIEventSimulator::MouseUp(int button)
{
    CGPoint pos;
    int x, y;
    wxGetMousePosition(&x, &y); 
    pos.x = x;
    pos.y = y;
    CGEventType type = CGEventTypeForMouseButton(button, false);
    CGEventRef event = CGEventCreateMouseEvent(NULL, type, pos, button);
    CGEventSetType(event, type);
    
    if (event)
    {
        CGEventPost(tap, event);
    }
    CFRelease(event);

    return true;
}

bool UIEventSimulator::KeyPress(int keycode, bool isDown, bool shiftDown, bool cmdDown, bool altDown)
{
    if (shiftDown)
        SendCharCode((CGCharCode)56, true);
    if (altDown)
        SendCharCode((CGCharCode)58, true);
    if (cmdDown)
        SendCharCode((CGCharCode)55, true);

    SendCharCode((CGCharCode)keycode, isDown);

    if (shiftDown)
        SendCharCode((CGCharCode)56, false);
    if (altDown)
        SendCharCode((CGCharCode)58, false);
    if (cmdDown)
        SendCharCode((CGCharCode)55, false);
    
    return true;
}

#endif

