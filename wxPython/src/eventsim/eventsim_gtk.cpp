/*
Copyright 2008 Kevin Ollivier
Licensed under the wxWidgets license
*/    

#include "UIEventSimulator.h"

#include <wx/defs.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

void SendButtonEvent(int button, bool isDown)
{
    int xbutton = 0;
    switch (button)
    {
        case wxMOUSE_BTN_LEFT:
            xbutton = 1;
            break;
        case wxMOUSE_BTN_RIGHT:
            xbutton = 2;
            break;
        case wxMOUSE_BTN_MIDDLE:
            xbutton = 3;
            break;
        default:
            wxFAIL_MSG("Unsupported button passed in.");
    }

    XEvent event;
    
    Display *display = XOpenDisplay(0);
    wxASSERT_MSG(display, "No display available!");
    
    memset(&event, 0x00, sizeof(event));
    
    if (isDown)
        event.type = ButtonPress;
    else
        event.type = ButtonRelease;

    event.xbutton.button = xbutton;
    event.xbutton.same_screen = True;
    
    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    event.xbutton.subwindow = event.xbutton.window;
    
    while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }
    
    XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0)
    XFlush(display);
    XCloseDisplay(display);
}

bool UIEventSimulator::MouseDown(int button)
{
    SendButtonEvent(button, true);
    return true;
}

bool UIEventSimulator::MouseMove(long x, long y)
{   
    Display *display = XOpenDisplay(0);
    wxASSERT_MSG(display, "No display available!");
    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    XFlush(display);
    XCloseDisplay(display);
    return true;
}

bool UIEventSimulator::MouseUp(int button)
{
    SendButtonEvent(button, false);
    return true;
}

bool UIEventSimulator::KeyPress(int keycode, bool isDown, bool shiftDown, bool cmdDown, bool altDown)
{
    Display *display = XOpenDisplay(0);
    wxASSERT_MSG(display, "No display available!");
    XTestFakeKeyEvent(display, keycode, isDown, 0);
    XFlush(display);
    XCloseDisplay(display);
    return true;
}

