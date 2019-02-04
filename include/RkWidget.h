/**
 * File name: RkWidget.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor (http://quamplex.com/redkite)
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef RK_WIDGET_H
#define RK_WIDGET_H

#include "Rk.h"

#ifdef RK_OS_WIN
#include <windows.h>
#elif RK_OS_MAC
 // to be defined
#else
#include <X11/Xlib.h>
#endif

#include <string>

class RkWidget {
  public:
#ifdef RK_OS_WIN
          using RkNativeWindow = HWND;
#elif RK_OS_MAC
          using RkNativeWindow = NSWindow;
#else
          using RkNativeWindow = uintptr_t;
#endif

          explicit RkWidget(RkWidget *parent = nullptr);
          explicit RkWidget(RkNativeWindow parent);
          virtual ~RkWidget();
	  void show();
          void setTitle(const std::string &title);
	  const std::string& title() const;
          RkNativeWindow nativeWindow();
          Display* display();

  private:

/**
 * Private implementations for platforms.
 * Not to be exposed to users.
 * This also provides ABI compatibility.
 */
#ifdef RK_OS_WIN
	  class RkWidgetXWin;
	  std::unique_ptr<RkWidgetWin> privateWidget;
#elif RK_OS_MAC
	  class RkWidgetMac;
	  std::unique_ptr<RkWidgetMac> privateWidget;
#else
          class RkWidgetXWin;
	  std::unique_ptr<RkWidgetXWin> privateWidget;
#endif

          std::string widgetTitle;
};

#endif // RK_WIDGET_H
