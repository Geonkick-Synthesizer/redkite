/**
 * File name: RkWidget.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://geontime.com>
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
#include "RkObject.h"
#include "RkCanvas.h"
#include "RkRect.h"
#include "RkColor.h"
#include "RkFont.h"

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
class RkFocusEvent;
class RkMain;
struct RkWindowId;
struct RkNativeWindowInfo;

class RK_EXPORT RkWidget: public RkObject, public RkCanvas {
  public:
          RK_CLASS_INFO(style_element, "RkWidget")
          RK_CLASS_INFO(style_class, "")
          RK_CLASS_INFO(style_id, "")

          explicit RkWidget(RkMain *mainApp, Rk::WindowFlags flags = Rk::WindowFlags::Widget);
          explicit RkWidget(RkMain *mainApp,
                            const RkNativeWindowInfo &parent,
                            Rk::WindowFlags flags = Rk::WindowFlags::Widget);
          explicit RkWidget(RkWidget *parent, Rk::WindowFlags flags = Rk::WindowFlags::Widget);
          virtual ~RkWidget();

	  void show(bool b = true);
	  bool isShown() const;
          void hide();
          void setTitle(const std::string &title);
	  const std::string& title() const;
          std::shared_ptr<RkNativeWindowInfo> nativeWindowInfo() const;
	  bool isClose() const;
          RkWidget* parentWidget() const;
          RkWidget* childWidget(const RkWindowId &id) const;
          void event(const RkEvent *event);
          RkWindowId id() const;
	  void setSize(int w, int h);
	  void setSize(const RkSize &size);
	  RkSize size() const;
	  void setWidth(int w);
	  int width() const;
          int minimumWidth() const;
          int maximumWidth() const;
          void setMinimumWidth(int width);
          void setMaximumWidth(int width);
	  void setHeight(int h);
	  int height() const;
          int minimumHeight() const;
          int maximumHeight() const;
          void setMinimumHeight(int height);
          void setMaximumHeight(int height);
          void setFixedWidth(int width);
          void setFixedHeight(int height);
          void setFixedSize(const RkSize &size);
          void setFixedSize(int width, int height);
          int x() const;
          void setX(int x);
          int y() const;
          void setY(int y);
          void setPosition(int x, int y);
          void setPosition(const RkPoint &p);
          RkPoint position() const;
          void setBorderWidth(int width);
          int borderWidth() const;
          void setBackgroundColor(int red, int green, int blue);
          void setBackgroundColor(const RkColor &color);
          const RkColor& background() const;
          void setBorderColor(int red, int green, int blue);
          const RkColor& borderColor() const;
          void setTextColor(const RkColor &color);
          const RkColor& textColor() const;
          const RkColor& color() const;
          void setColor(const RkColor &color);
          const RkFont& font() const;
          void setFont(const RkFont &font);
          RkCanvasInfo getCanvasInfo() const override;
          RkRect rect() const;
          void update();
          void close();
          Rk::Modality modality() const;
          bool isModal() const;
          void setWidgetAttribute(Rk::WidgetAttribute attribute);
          void clearWidgetAttribute(Rk::WidgetAttribute attribute);
          Rk::WidgetAttribute widgetAttributes() const;
          void enableInput();
          void disableInput();
          bool isInputEnabled() const;
          RkWidget* getTopWindow() const;
          void enableGrabKey(bool b);
          bool grabKeyEnabled() const;
          void propagateGrabKey(bool b);
          bool propagateGrabKeyEnabled() const;
          void setEventQueue(RkEventQueue *eventQueue);
          void setFocus(bool b = true);
          bool hasFocus() const;
          void setPointerShape(Rk::PointerShape shape);
          Rk::PointerShape pointerShape() const;

  protected:
          RK_DECLARE_IMPL(RkWidget);
          RkWidget(RkWidget *parent, const std::shared_ptr<RkWidgetImpl> &impl);
          virtual void closeEvent(const RkCloseEvent *event);
          virtual void keyPressEvent(const RkKeyEvent *event);
          virtual void keyReleaseEvent(const RkKeyEvent *event);
          virtual void mouseMoveEvent(const RkMouseEvent *event);
          virtual void mouseButtonPressEvent(const RkMouseEvent *event);
          virtual void mouseButtonReleaseEvent(const RkMouseEvent *event);
          virtual void mouseDoubleClickEvent(const RkMouseEvent *event);
          virtual void wheelEvent(const RkWheelEvent *event);
          virtual void moveEvent(const RkMoveEvent *event);
          virtual void resizeEvent(const RkResizeEvent *event);
          virtual void paintEvent(const RkPaintEvent *event);
          virtual void showEvent(const RkShowEvent *event);
          virtual void hideEvent(const RkHideEvent *event);
          virtual void focusEvent(const RkFocusEvent *event);

 private:
          RK_DISABLE_COPY(RkWidget);
          RK_DISABLE_MOVE(RkWidget);
};

#endif // RK_WIDGET_H
