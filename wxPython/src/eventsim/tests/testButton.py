import unittest
import wx
import eventsim
        

class ButtonTestApp(wx.App):
    def __init__(self):
        wx.App.__init__(self, redirect=False)

    def OnInit(self):
        self.frame = wx.Frame(parent=None, id=wx.ID_ANY)
        self.testControl = wx.Button(parent=self.frame)
        self.testControl.Bind(wx.EVT_BUTTON, self.OnClick)
        self.SetTopWindow(self.frame)
        self.frame.Show()
        self.clickFired = False
        
        timer = wx.CallLater(100, self.ExitMainLoop)
        pos = self.testControl.ClientToScreen(self.testControl.GetPosition())
        tester = eventsim.UIEventSimulator()
        tester.MouseMove(pos.x, pos.y)
        tester.MouseDown(0)
        tester.MouseUp(0)
        
        return True
        
    def OnExit(self):
        print "Click Did Fire: " + `self.clickFired`
    
    def OnClick(self, event):
        self.clickFired = True
        
class TextCtrlTestApp(wx.App):
    def __init__(self):
        wx.App.__init__(self, redirect=False)

    def OnInit(self):
        self.frame = wx.Frame(parent=None, id=wx.ID_ANY)
        self.testControl = wx.TextCtrl(parent=self.frame)
        self.testControl.Bind(wx.EVT_CHAR, self.OnChar)
        self.SetTopWindow(self.frame)
        self.frame.Show()
        self.charFired = False
        
        timer = wx.CallLater(100, self.ExitMainLoop)
        self.testControl.SetFocus()
        tester = eventsim.UIEventSimulator()
        
        tester.KeyChar(ord('a'))
        
        return True
        
    def OnExit(self):
        print "Key Did Fire: " + `self.charFired`
    
    def OnChar(self, event):
        if event.GetKeyCode() == ord('a'):
            self.charFired = True
        

if __name__ == '__main__':
    #unittest.main()
    app = ButtonTestApp()
    app.MainLoop()
    
    app = TextCtrlTestApp()
    app.MainLoop()
   