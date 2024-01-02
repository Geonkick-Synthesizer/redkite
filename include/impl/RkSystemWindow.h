/**
 * File name: RkSystemWindow.h
 * Project: Redkite (A lightweight graphics widget toolkit for embedded GUI)
 *
 * Copyright (C) 2023 Iurie Nistor 
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

#ifndef RK_SYSTEM_WINDOW_H
#define RK_SYSTEM_WINDOW_H

#include "Rk.h"
#include "RkObject.h"
#include "RkEventQueue.h"
#include "RkCanvas.h"
#include "RkRect.h"
#include "RkColor.h"
#include "RkFont.h"

class RkEvent;
class RkCloseEvent;
class RkKeyEvent;
class RkMouseEvent;
class RkWheelEvent;
class RkDropEvent;
class RkMoveEvent;
class RkResizeEvent;
class RkPaintEvent;
class RkShowEvent;
class RkHideEvent;
class RkFocusEvent;
class RkHoverEvent;
class RkMain;
struct RkWindowId;
class RkNativeWindowInfo;

#ifdef RK_OS_WIN
class RkWindowWin;
#else // GNU/Linux
class RkWindowX;
#endif // GNU/Linux

class RkSystemWindow {
public:
        explicit RkSystemWindow(RkMain& mainApp,
                                Rk::WindowFlags flags = Rk::WindowFlags::Widget);
        explicit RkSystemWindow(RkMain& mainApp,
                                const RkNativeWindowInfo &parent,
                                Rk::WindowFlags flags = Rk::WindowFlags::Widget);
        virtual ~RkWidget();
        Rk::WindowFlags windowFlags() const;
        void show(bool b = true);
        bool isShown() const;
        void hide();
        void setTitle(const std::string &title);
        const std::string& title() const;
        const RkNativeWindowInfo* nativeWindowInfo() const;
        bool isClose() const;
        RkWidget* parentWidget() const;
        RkWindowId id() const;
        void setSize(const RkSize &size);
        RkSize size() const;
        void setPosition(const RkPoint &p);
        RkPoint position() const;
        void setBackgroundColor(const RkColor &color);
        const RkColor& background() const;
        void setTextColor(const RkColor &color);
        const RkColor& textColor() const;
        const RkColor& color() const;
        void setColor(const RkColor &color);
        const RkFont& font() const;
        void setFont(const RkFont &font);
        RkRect rect() const;
        void update();
        void close();
        void setWidgetAttribute(Rk::WidgetAttribute attribute);
        void clearWidgetAttribute(Rk::WidgetAttribute attribute);
        Rk::WidgetAttribute widgetAttributes() const;
        void setTopWidget(RkWidget *widget);
        RkWidget* getTopWidget() const;
        void enableGrabKey(bool b);
        bool grabKeyEnabled() const;
        void propagateGrabKey(bool b);
        bool propagateGrabKeyEnabled() const;
        void setFocus(bool b = true);
        bool hasFocus() const;
        void setPointerShape(Rk::PointerShape shape);
        Rk::PointerShape pointerShape() const;
        void setScaleFactor(double factor);
        double scaleFactor() const;

        void closeEvent(RkCloseEvent *event);
        void keyPressEvent(RkKeyEvent *event);
        void keyReleaseEvent(RkKeyEvent *event);
        void shortcutEvent(RkKeyEvent *event);
        void mouseMoveEvent(RkMouseEvent *event);
        void mouseButtonPressEvent(RkMouseEvent *event);
        void mouseButtonReleaseEvent(RkMouseEvent *event);
        void mouseDoubleClickEvent(RkMouseEvent *event);
        void wheelEvent(RkWheelEvent *event);
        void dropEvent(RkDropEvent *event);
        void moveEvent(RkMoveEvent *event);
        void resizeEvent(RkResizeEvent *event);
        void paintEvent(RkPaintEvent *event);
        void showEvent(RkShowEvent *event);
        void hideEvent(RkHideEvent *event);
        void focusEvent(RkFocusEvent *event);
        void hoverEvent(RkHoverEvent *event);

private:
#ifdef RK_OS_WIN
        std::unique_ptr<RkWindowWin> platformWindow;
#else // GNU/Linux
        std::unique_ptr<RkWindowX> platformWindow;
#endif // GNU/Linux
        std::string windowTitle;
        RkSize windowSize;
        RkColor windowBackground;
        Rk::WidgetAttribute windowAttributes;
        RkColor windowTextColor;
        RkColor windowDrawingColor;
        RkFont windowFont;
        Rk::PointerShape widgetPointerShape;
        bool isGrabKeyEnabled;
        bool isPropagateGrabKey;
};

#endif // RK_SYSTEM_WINDOW_H
