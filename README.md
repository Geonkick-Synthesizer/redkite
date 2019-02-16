# Redkite

#### Description

A small GUI toolkit.

License: GPLv3

Status: development, no release yet.

### Requirements & goals

Here are some requirements ideas that makes this
toolkit to differ from common ones. Also, these requirements
makes possible to develop self sufficient GUI plugins apart of the
common usage.

* Generally have the sample properties as common ones.

* Must not have a global state. Many instances
  of the sample toolkit version or different must be able to run without problems
  in the sample process address a space. No static global variables
  or other interference.

* Can be linked statically into a shred library that uses the tookit
  and that shared library to be loaded dynamically.
  Loading these kinds of shared libraries (linked against the same
  tookit version or not) in the same address process space must run
  without problems, there must be no interference between
  toolkit instances and versions.

* Can be linked statically.

* Platforms: GNU/Linux (XWindow System backend), Windows (Win API backend), Mac (no plans yet)

