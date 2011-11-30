/*
Copyright 2008 Kevin Ollivier
Licensed under the wxWidgets license
*/

#include "UIEventSimulator.h"

UIEventSimulator::UIEventSimulator()
{
}

UIEventSimulator::~UIEventSimulator()
{
}


bool UIEventSimulator::MouseClick(int button) 
{
    MouseDown(button);
    MouseUp(button);
    
    return true;
}

bool UIEventSimulator::MouseDblClick(int button) 
{
    MouseDown(button);
    MouseUp(button);
    MouseDown(button);
    MouseUp(button);
    
    return true;
}

bool UIEventSimulator::MouseDragDrop(long x1, long y1, long x2, long y2, int button)
{
    MouseMove(x1, y1);
    MouseDown(button);
    MouseMove(x2, y2);    
    MouseUp(button);
    
    return true;
}

bool  UIEventSimulator::KeyChar(int keycode, bool shiftDown, bool cmdDown, bool altDown)
{
    KeyPress(keycode, false, shiftDown, cmdDown, altDown);
    KeyPress(keycode, true, shiftDown, cmdDown, altDown);
    
    return true;
} 
