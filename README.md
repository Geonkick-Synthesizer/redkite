# Redkite

#### Description

Redkite is a small free software GUI toolkit.
It is developed in C++17 and inspired from other
well known GUI toolkits.

Version: 0.6.3

License: GPLv3

Author: Iurie Nistor

Note: Redkite is not supposed to be provided as shared library,
      it must be only as static library for development.

#### The problem

An application that is developed in a particular GUI toolkit is loading
in its address space GUI plugins that are developed with different versions
of the same or different GUI toolkit. Using well known GUI toolkits for this
purpose can cause a lot of conflicts. For example, often these conflicts arise
in music software when a Digital Audio Workstation as a host is loading GUI
audio plugins. The Redkite GUI toolkit is developed to address
this issue, and provide a way to develop easily self-sufficiency
GUI plugins apart from developing standalone applications.

### Goals

 * Generally to have the same basic properties as common GUI toolkits.

 * Many instances of the same or different version of the toolkit must be able
   to run without problems in the same process address space.

 * Can be easily linked statically. Shared libraries that are developed
   using the toolkit and loaded dynamically must not cause conflicts.

 * Not to add dependencies that breaks the above points. Also, maximum
   to relay on dependencies for runtime that are provided by default
   by the system. Avoid requiring to install additional dependencies
   for runtime that may cause versioning conflicts.

 * Be cross-platform

 * Interface (API) to be simple

### What was implemented

* Widgets: RkWidget, RkLabel, RkLineEdit
* Graphics: RkPainter, RkImage. RkPainter paints on RkWidget and RkImage.
  RkPainter uses Cairo backend.
* Actions: a binding mechanism between objects. An action can be posted in thread-safe manner.
* GNU/Linux (XLib/X11)
* CMake system, build/install
* rkpng2c - a tool that converts PNG images to C array encoded in ARGB32
* RkTimer - a timer class

Interface classes that now are implemented with the purpose of extending their functionality:

* RkCanvas
* RkColor
* RkEvent
* RkEventQueue
* RkImage
* RkButton
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
* RkTimer
* RkLineEdit
* RkProgressBar
* RkWidget

### Build & Install Redkite

In order to build Redkite there is a need to install the following development packages:

* Cairo

On Debian, Ubuntu, Ubuntu Studio install:

    apt-get install build-essential
    apt-get install cmake
    apt-get install libcairo2-dev

Clone the code repository, compile and install

        git clone https://gitlab.com/geontime/redkite.git
        mkdir redkite/build
        cd redkite/build
        cmake ../
        make
        make install

### What applications were developed with Redkite?

* [Geonkick](https://gitlab.com/geontime/geonkick) - a percussion synthesizer.
