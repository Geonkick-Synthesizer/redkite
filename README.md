# Redkite

#### Description

A small GUI toolkit.

Version: 1.0

License: GPLv3

Author: Iurie Nistor

Status: active development, no release yet

### What was implemented

* Widgets: RkWidget, RkLabel
* Graphics: RkPainter, RkImage. RkPainter paints on RkWidget and RkImage.
  RkPainter uses Cairo backend.
* Cross-platform: GNU/Linux (X11), Windows (Win API). Not plans now for Mac.
* CMake build/install
* rkpng2c - a tool that converts PNG images to C array encoded in ARGB32.

Interface classes that now are implemented with the purpose of extending their functionality:

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
* RkFont
* RkPlatform
* RkPoint
* RkRealPoint
* RkRect
* RkSize
* RkWidget

### Requirements & goals

Here are some requirements ideas that makes this
toolkit different from common ones. Also, these requirements
makes possible to develop with the toolkit self-sufficient GUI
plugins (for example, necessary for music applications)
apart of the common usage.

* Generally have the same basic properties as common ones.

* Must not have a global state. Many instances
  of the same toolkit version or different must be able
  to run without problems in the same process address space.

* Can be linked statically into a shared library that uses the tookit,
  and that shared library to be loaded dynamically by the host.
  Loading these kinds of shared libraries (linked against the same
  tookit version or not) in the same address process space must run
  without problems, there must be no interference between
  toolkit instances and versions.

* Can be easily linked statically.

* User interface API to be simple.

* Be cross-platform.
