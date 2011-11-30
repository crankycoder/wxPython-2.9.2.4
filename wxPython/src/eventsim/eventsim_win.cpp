/*
Copyright 2008 Kevin Ollivier
Licensed under the wxWidgets license
*/    

#include "UIEventSimulator.h"

#include <wx/defs.h>
#include <windows.h>

DWORD EventTypeForMouseButton(int button, bool isDown)
{
    switch (button)
    {
        case wxMOUSE_BTN_LEFT:
            if (isDown)
                return MOUSEEVENTF_LEFTDOWN;
            else
                return MOUSEEVENTF_LEFTUP;
        case wxMOUSE_BTN_RIGHT:
            if (isDown)
                return MOUSEEVENTF_RIGHTDOWN;
            else
                return MOUSEEVENTF_RIGHTUP;
        case wxMOUSE_BTN_MIDDLE:
            if (isDown)
                return MOUSEEVENTF_MIDDLEDOWN;
            else
                return MOUSEEVENTF_MIDDLEUP;
            
        default:
            wxFAIL_MSG("Unsupported button passed in.");
            return -1;
    }
}

bool UIEventSimulator::MouseDown(int button)
{
    POINT p;
    GetCursorPos(&p);
    mouse_event(EventTypeForMouseButton(button, false), p.x, p.y, 0, 0);
    return true;
}

bool UIEventSimulator::MouseMove(long x, long y)
{   
    mouse_event(MOUSEEVENTF_MOVE, p.x, p.y, 0, 0);
    return true;
}

bool UIEventSimulator::MouseUp(int button)
{
    POINT p;
    GetCursorPos(&p);
    mouse_event(EventTypeForMouseButton(button, false), p.x, p.y, 0, 0);
    return true;
}

bool UIEventSimulator::KeyPress(int keycode, bool isDown, bool shiftDown, bool cmdDown, bool altDown)
{
    DWORD flags = 0;
    if (isDown)
        flags = KEYEVENTF_KEYUP;
    keybd_event(wxCharCodeWXToMSW(keycode), 0, flags, 0);
    return true;
}

