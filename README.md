# Redkite
1;4601;0c
#### Description

A small GUI toolkit.

License: GPLv3

Status: development, no release yet.

### What was implemented

* Widgets: RkWidget, RkLabel
* Graphics: RkPainter, RkImage. RkPainter paints on RkWidgets and RkImage.
  RkPainter uses Cairo backend.
* Cross-platform: GNU/Linux (X11), Windows (Win API)
* CMake build/install
* rkpng2c - a tool that covnerts PNG images to C array econded in ARGB32

Interface classes that now are implemented with the purprose of exteding their functionality.

* RkCanvas
* RkColor
* RkEvent
* RkEventQueue
* RkImage
* RkLabel
* RkLog
* RkMain
* RkPainter
* RkPen
* RkPlatform
* RkPoint
* RkRealPoint
* RkRect
* RkSize
* RkWidget

### Requirements & goals

Here are some requirements ideas that makes this
toolkit different from common ones. Also, these requirements
makes possible to develop self sufficient GUI plugins apart of the
common usage.

* Generally have the same properties as common ones.

* Must not have a global state. Many instances
  of the same toolkit version or different must be able to run without problems
  in the same process address space.

* Can be linked statically into a shared library that uses the tookit
  and that shared library to be loaded dynamically.
  Loading these kinds of shared libraries (linked against the same
  tookit version or not) in the same address process space must run
  without problems, there must be no interference between
  toolkit instances and versions.

* Can be linked statically.

* Platforms: GNU/Linux (XWindow System backend), Windows (Win API backend), MacOS (no plans yet)


