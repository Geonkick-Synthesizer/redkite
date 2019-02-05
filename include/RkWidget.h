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
          RkWidget(const RkWidget &other) = delete;
          RkWidget& operator=(const RkWidget &other) = delete;
          RkWidget(RkWidget &&other) = delete;
          RkWidget& operator=(RkWidget &&other) = delete;
	  void show();
          void setTitle(const std::string &title);
	  const std::string& title() const;
          RkNativeWindow nativeWindow();
	  void pocessEvents();

	  virtual void closeEvent(std::shared_ptr<RkCloseEvent> &event)
	  virtual void keyPressEvent(std::shared_ptr<RkKeyEvent> &event);
     	  virtual void keyReleaseEvent(std::shared_ptr<RkKeyEvent> &event);
 	  virtual void paintEvent(std::shared_ptr<RkPainEvent> &event);
	  virtual void mousePressEvent(std::shared_ptr<RkMouseEvent> &event);
  	  virtual void mouseReleaseEvent(std::shared_ptr<RkMouseEvent> &event);
	  virtual void mouseDoubleClickEvent(std::shared_ptr<RkMouseEvent> &event);
 	  virtual void mouseMoveEvent(std::shared_ptr<RkMouseEvent> &event);
 	  virtual void paintEvent(std::shared_ptr<RkPainEvent> &event);
	  virtual void wheelEvent(std::shared_ptr<RkPainEvent> &event);
	  virtual void resizeEvent(std::shared_ptr<RkResizeEvent> &event);
	  virtual void showEvent(std::shared_ptr<RkShowEvent> &event);
	  virtual void hideEvent(std::shared_ptr<RkHideEvent> &event);

  private:
          void processChildEvents();

/**
 * Private implementations for platforms.
 * Not to be exposed to users.
 * This also provides ABI compatibility.
 */
#ifdef RK_OS_WIN
	  RK_PRIVATE_IMPL(RkWidgetXWin, privateWidget)
#elif RK_OS_MAC
	  RK_PRIVATE_IMPL(RkWidgetMac, privateWidget)
#else
	  RK_PRIVATE_IMPL(RkWidgetXWin, privateWidget)
#endif

	  std::string widgetTitle;
          std::list<std::shared_ptr<RkWidget>> childWidgets;
};

#endif // RK_WIDGET_H
