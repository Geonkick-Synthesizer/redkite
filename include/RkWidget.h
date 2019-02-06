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

#include <string>

class RkCloseEvent;
class RkKeyEvent;
class RkMouseEvent;
class RkWheelEvent;
class RkMoveEvent;
class RkResizeEvent;
class RkPaintEvent;
class RkShowEvent;
class RkHideEvent;

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

          virtual void closeEvent(const std::shared_ptr<RkCloseEvent> &event);
          virtual void keyPressEvent(const std::shared_ptr<RkKeyEvent> &event);
          virtual void keyReleaseEvent(const std::shared_ptr<RkKeyEvent> &event);
          virtual void mouseMoveEvent(const std::shared_ptr<RkMouseEvent> &event);
          virtual void mouseButtonPressEvent(const std::shared_ptr<RkMouseEvent> &event);
          virtual void mouseButtonReleaseEvent(const std::shared_ptr<RkMouseEvent> &event);
          virtual void mouseDoubleClickEvent(const std::shared_ptr<RkMouseEvent> &event);
          virtual void wheelEvent(const std::shared_ptr<RkWheelEvent> &event);
          virtual void moveEvent(const std::shared_ptr<RkMoveEvent> &event);
          virtual void resizeEvent(const std::shared_ptr<RkResizeEvent> &event);
          virtual void paintEvent(const std::shared_ptr<RkPaintEvent> &event);
          virtual void showEvent(const std::shared_ptr<RkShowEvent> &event);
          virtual void hideEvent(const std::shared_ptr<RkHideEvent> &event);

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
