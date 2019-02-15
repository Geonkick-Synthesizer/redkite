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
#include <unordered_map>

class RkEvent;
class RkCloseEvent;
class RkKeyEvent;
class RkMouseEvent;
class RkWheelEvent;
class RkMoveEvent;
class RkResizeEvent;
class RkPaintEvent;
class RkShowEvent;
class RkHideEvent;
struct RkWindowId;
struct RkNativeWindowInfo;

class RkWidget {
  public:
          RK_CLASS_INFO(style_element, "RkWidget")
          RK_CLASS_INFO(style_class, "")
          RK_CLASS_INFO(style_id, "")

          explicit RkWidget(RkWidget *parent = nullptr);
          explicit RkWidget(const RkNativeWindowInfo &parent);
          virtual ~RkWidget();
          RkWidget(const RkWidget &other) = delete;
          RkWidget& operator=(const RkWidget &other) = delete;
          RkWidget(RkWidget &&other) = delete;
          RkWidget& operator=(RkWidget &&other) = delete;

	  void show();
          void setTitle(const std::string &title);
	  const std::string& title() const;
          std::shared_ptr<RkNativeWindowInfo> nativeWindowInfo() const;
	  bool isClose() const;
	  void processEvents();
          RkWidget* parent() const;
          RkWidget* child(const RkWindowId &id) const;
          void processEvent(const std::shared_ptr<RkEvent> &event);
          RkWindowId id() const;

	  void setSize(int w, int h);
	  void setSize(const std::pair<int, int> &size);
	  std::pair<int, int> size() const;
	  void setWidth(int w);
	  int width() const;
	  void setHeight(int h);
	  int height() const;
          int x() const;
          void setX(int x);
          int y() const;
          void setY(int y);
          void setPosition(const std::pair<int, int> &position);
          std::pair<int, int> position() const;
          void setBorderWidth(int width);
          void setBackgroundColor(int red, int green, int blue);
          void setBorderColor(int red, int green, int blue);

  protected:
          RK_DECLARE_IMPL(RkWidget)
          RkWidget(RkWidget *parent, const std::shared_ptr<RkWidgetImpl> &impl);

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
          void addChild(RkWidget* child);
};

#endif // RK_WIDGET_H
