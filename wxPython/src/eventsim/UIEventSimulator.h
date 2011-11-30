/*
Copyright 2008 Kevin Ollivier
Licensed under the wxWidgets license
*/

#ifndef _UIEVENTSIMULATOR_H_
#define _UIEVENTSIMULATOR_H_

#include <wx/defs.h>
#include <wx/event.h>
#include <wx/dynarray.h>

#ifdef __WXGTK__
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#endif

class UIEventSimulator
{
  public:
    UIEventSimulator();
    ~UIEventSimulator();
    
    // Mouse related
    bool        MouseMove(long x, long y);
    bool        MouseDown(int button = wxMOUSE_BTN_LEFT);
    bool        MouseUp(int button = wxMOUSE_BTN_LEFT);
    bool        MouseClick(int button = wxMOUSE_BTN_LEFT);
    bool        MouseDblClick(int button = wxMOUSE_BTN_LEFT);
    bool        MouseDragDrop(long x1, long y1, long x2, long y2, int button = wxMOUSE_BTN_LEFT);
    
    // Keyboard related:
    bool        KeyPress(int keycode, bool isDown=true, bool shiftDown=false, bool cmdDown=false, bool altDown=false);
    bool        KeyChar(int keycode, bool shiftDown=false, bool cmdDown=false, bool altDown=false);
};

#endif
