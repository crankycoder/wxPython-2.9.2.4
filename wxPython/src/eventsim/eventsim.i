%module(package="wx") eventsim

%{
#include "wx/wxPython/wxPython.h"
#include "wx/wxPython/pyclasses.h"
#include "UIEventSimulator.h"
%}

//---------------------------------------------------------------------------

%include UIEventSimulator.h
