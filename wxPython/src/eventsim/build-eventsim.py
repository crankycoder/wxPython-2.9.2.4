#!/usr/bin/python

import os, string, sys
import commands
import wx.build.config
import distutils.sysconfig

def getwxPythonIncludesDir(prefix):
    wxPyDirs = ["include/wx-2.8/wx/wxPython/i_files",
                "include/wx/wxPython/i_files",
                "wxPython/src",
                "../wxPython/src"]
    for wxdir in wxPyDirs:
        path = os.path.join(prefix, wxdir)
        if os.path.exists(path):
            return path
            
    return None

osname = ""
if sys.platform.startswith("win"):
    osname = "win"
elif sys.platform.startswith("darwin"):
    osname = "mac"
elif sys.platform.startswith("linux"):
    osname = "linux"
else:
    print "WARNING: unknown platform. Defaulting to 'linux' as most Unix variants will build in this config."
    osname = "linux"
    
    
wxRoot = ""
if osname == "win":
    wxRoot = os.environ["WXWIN"]
    wxBakefiles = os.path.join(wxRoot, "build", "bakefiles")
else:
    wxRoot = commands.getoutput("wx-config --prefix")
    wxBakefiles = os.path.join(wxRoot, "share", "bakefile") 
    
if not os.path.exists(wxRoot):
    print "ERROR: Cannot find wxWidgets root install dir."
    if osname == "win":
        print "Make sure you've set the WXWIN environment variable to the wx root directory."
    else:
        print "Make sure wx-config is on your PATH."
        
    sys.exit(1)

if os.environ.has_key("BAKEFILE_PATHS"):
    os.environ["BAKEFILE_PATHS"] = os.environ["BAKEFILE_PATHS"] + ":" + wxBakefiles
else:
    os.environ["BAKEFILE_PATHS"] = wxBakefiles    

os.system("bakefile -f gnu eventsim.bkl")

swigFlags = string.join(wx.build.config.swig_args, ' ')
wxPyInclude = getwxPythonIncludesDir(wxRoot)
pylibdir = distutils.sysconfig.PREFIX
if osname == "win":
    pylibdir = os.path.join(pylibdir, "Libs")
else:
    pylibdir = os.path.join(pylibdir, "lib")

dllflag = "-shared"
bundleflag = "-shared"

if osname == "mac":
    dllflag = "-dynamiclib"
    bundleflag = "-bundle"
    
target = ""
if "--clean" in sys.argv:
    target = "clean"

os.system("swig %s -I%s -o eventsim_swig.cpp eventsim.i" % (swigFlags, wxPyInclude))

os.system("""make %s LINK_MODULE_FLAGS="%s" LINK_DLL_FLAGS="%s" CXXFLAGS="-I %s" PLATFORM_OS="%s" PYTHON_VERSION="%s" PYTHON_LIBDIR="%s" """ % \
            (target, bundleflag, dllflag, distutils.sysconfig.get_python_inc(), osname, str(sys.version_info[0]) + str(sys.version_info[1]), pylibdir) )

