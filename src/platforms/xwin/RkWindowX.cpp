/**
 * File name: RkWindowX.cpp
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

#include "RkLog.h"
#include "RkWindowX.h"
#include "RkCanvasInfo.h"

#include "X11/cursorfont.h"

RkWindowX::RkWindowX(const RkNativeWindowInfo *parent, Rk::WindowFlags flags)
        : parentWindowInfo{parent ? *parent : RkNativeWindowInfo() }
         , xDisplay{parent ? parent->display : nullptr}
         , screenNumber{parent ? parent->screenNumber : 0}
         , xWindow{0}
         , winBorderWidth{0}
         , winBorderColor{255, 255, 255}
         , winBackgroundColor{255, 255, 255}
         , canvasInfo{nullptr}
         , windowInfo{nullptr}
         , windowFlags{flags}
 {
         RK_LOG_DEBUG("called: d: " << xDisplay << ", s: " << screenNumber);
 }

RkWindowX::RkWindowX(const RkNativeWindowInfo &parent, Rk::WindowFlags flags)
        : parentWindowInfo{parent}
        , xDisplay{parent.display}
        , screenNumber{parent.screenNumber}
        , xWindow{0}
        , winBorderWidth{0}
        , winBorderColor{255, 255, 255}
        , winBackgroundColor{255, 255, 255}
        , canvasInfo{nullptr}
        , windowInfo{nullptr}
        , windowFlags{flags}
{
        RK_LOG_DEBUG("called: d: " << xDisplay << ", s: " << screenNumber);
}

RkWindowX::~RkWindowX()
{
        RK_LOG_DEBUG("called");
        if (xDisplay) {
                freeCanvasInfo();
                XDestroyWindow(xDisplay, xWindow);
                if (!hasParent())
                        XCloseDisplay(xDisplay);
        }
}

bool RkWindowX::hasParent() const
{
        return parentWindowInfo.display != nullptr;
}

bool RkWindowX::openDisplay()
{
        xDisplay = XOpenDisplay(nullptr);
        screenNumber = DefaultScreen(xDisplay);
        return xDisplay != nullptr;
}

bool RkWindowX::init()
{
        RK_LOG_DEBUG("called");
        if (!hasParent()) {
                if (!openDisplay()) {
                        RK_LOG_ERROR("can't open display");
                        return false;
                }
	}

        Window parent = 0;
        if (static_cast<int>(windowFlags) & static_cast<int>(Rk::WindowFlags::Dialog)) {
                RK_LOG_DEBUG("is dialog, get root window");
                parent = RootWindow(xDisplay, screenNumber);
        } else {
                parent = hasParent() ? parentWindowInfo.window : RootWindow(xDisplay, screenNumber);
        }
        auto pos = position();
        auto winSize = size();
        RK_LOG_DEBUG("create window: d: " << xDisplay << ", p: " << parent);
        xWindow = XCreateSimpleWindow(xDisplay, parent,
                                      pos.x(), pos.y(),
                                      winSize.width(), winSize.height(), winBorderWidth,
                                      pixelValue(winBorderColor),
                                      pixelValue(winBackgroundColor));
        if (!xWindow) {
                RK_LOG_ERROR("can't create window");
                return false;
        }

        if ((static_cast<int>(windowFlags) & static_cast<int>(Rk::WindowFlags::Dialog)) && hasParent())
                XSetTransientForHint(xDisplay, xWindow, parentWindowInfo.window);

        XSelectInput(xDisplay, xWindow, ExposureMask
                                        | KeyPressMask | KeyReleaseMask
                                        | ButtonPressMask | ButtonReleaseMask | PointerMotionMask
                                        | StructureNotifyMask | FocusChangeMask
                                        | EnterWindowMask | LeaveWindowMask);

        deleteWindowAtom = XInternAtom(display(), "WM_DELETE_WINDOW", True);
        XSetWMProtocols(xDisplay, xWindow, &deleteWindowAtom, 1);
        createCanvasInfo();
        windowInfo = std::make_unique<RkNativeWindowInfo>();
        windowInfo->display = xDisplay;
        windowInfo->screenNumber = screenNumber;
        windowInfo->window = xWindow;
        RK_LOG_DEBUG("window created");
        return true;
}

void RkWindowX::show(bool b)
{
        if (isWindowCreated()) {
                if (b)
                        XMapRaised(display(), xWindow);
                else
                        XUnmapWindow(display(), xWindow);
        }
}

Display* RkWindowX::display() const
{
        return xDisplay;
}

const RkNativeWindowInfo* RkWindowX::nativeWindowInfo() const
{
        return windowInfo ? windowInfo.get() : nullptr;
}

void RkWindowX::setTitle(const std::string &title)
{
        if (isWindowCreated() && !title.empty())
                XStoreName(xDisplay, xWindow, title.c_str());
}

bool RkWindowX::isWindowCreated() const
{
        return xDisplay != nullptr && xWindow;
}

RkSize RkWindowX::size() const
{
        if (isWindowCreated()) {
                XWindowAttributes attributes;
                XGetWindowAttributes(xDisplay, xWindow, &attributes);
                return RkSize(attributes.width, attributes.height);
        }

        return {250, 250};
}

void RkWindowX::setSize(const RkSize &size)
{
        if (size.width() > 0 && size.height() > 0) {
                if (isWindowCreated())
                        XResizeWindow(display(), xWindow, size.width(), size.height());
        }
}

RkPoint RkWindowX::position() const
{
        if (isWindowCreated()) {
                XWindowAttributes attributes;
                XGetWindowAttributes(xDisplay, xWindow, &attributes);
                return RkPoint(attributes.x, attributes.y);
        }
        return {0, 0};
}

void RkWindowX::setPosition(const RkPoint &position)
{
        if (isWindowCreated())
                XMoveWindow(display(), xWindow, position.x(), position.y());
}

void RkWindowX::setBorderWidth(int width)
{
        winBorderWidth = width;
        if (isWindowCreated())
                XSetWindowBorderWidth(display(), xWindow, winBorderWidth);
}

int RkWindowX::borderWidth() const
{
        return winBorderWidth;
}

unsigned long RkWindowX::pixelValue(const RkColor &color)
{
        if (!display())
                return 0;

        auto colorMap = XDefaultColormap(display(), screenNumber);
        XColor pixelColor;
        pixelColor.flags = DoRed | DoGreen | DoBlue;
        constexpr const unsigned short k = 65535 / 255;
        pixelColor.red   = k * color.red();
        pixelColor.green = k * color.green();
        pixelColor.blue  = k * color.blue();

        auto res = XAllocColor(display(), colorMap, &pixelColor);
        if (!res) {
                RK_LOG_ERROR("can't allocate color");
                return 0;
        }

        return pixelColor.pixel;
}

void RkWindowX::setBorderColor(const RkColor &color)
{
        winBorderColor = color;
        if (isWindowCreated())
                XSetWindowBorder(display(), xWindow, pixelValue(winBorderColor));
}

const RkColor& RkWindowX::borderColor() const
{
        return winBorderColor;
}

void RkWindowX::setBackgroundColor(const RkColor &color)
{
        winBackgroundColor = color;
        if (isWindowCreated())
                XSetWindowBackground(display(), xWindow, pixelValue(winBackgroundColor));
}

const RkColor& RkWindowX::background() const
{
        return winBackgroundColor;
}

RkWindowId RkWindowX::id() const
{
        RkWindowId id;
        id.id = xWindow;
        return id;
}

void RkWindowX::update()
{
        if (isWindowCreated()) {
                XExposeEvent event;
                event.type       = Expose;
                event.send_event = false;
                event.display    = display();
                event.window     = xWindow;
                event.x          = 0;
                event.y          = 0;
                event.width      = size().width();
                event.height     = size().height();
                event.count      = 0;
                XSendEvent(display(),
                           xWindow,
                           True,
                           ExposureMask,
                           reinterpret_cast<XEvent*>(&event));
        }
}

#ifdef RK_GRAPHICS_CAIRO_BACKEND
void RkWindowX::createCanvasInfo()
{
        canvasInfo = std::make_unique<RkCanvasInfo>();
        canvasInfo->cairo_surface = cairo_xlib_surface_create(display(), xWindow,
                                                              DefaultVisual(display(), screenNumber),
                                                              size().width(), size().height());
}

void RkWindowX::resizeCanvas()
{
        cairo_xlib_surface_set_size(canvasInfo->cairo_surface,
                                    size().width(),
                                    size().height());
}

const RkCanvasInfo* RkWindowX::getCanvasInfo() const
{
        return canvasInfo ? canvasInfo.get() : nullptr;
}

void RkWindowX::freeCanvasInfo()
{
        if (canvasInfo)
                cairo_surface_destroy(canvasInfo->cairo_surface);
}

#else
#error No graphics backend defined
#endif // RK_GRAPHICS_CAIRO_BACKEND

void RkWindowX::setFocus(bool b)
{
        if (b)
                XSetInputFocus(display(),
                               xWindow,
                               RevertToParent,
                               CurrentTime);
        else
                XSetInputFocus(display(),
                               None,
                               RevertToParent,
                               CurrentTime);
}

bool RkWindowX::hasFocus() const
{
        Window focus_return;
        int revert_to;
        XGetInputFocus(display(), &focus_return, &revert_to);
        return focus_return == xWindow;
}

void RkWindowX::setPointerShape(Rk::PointerShape shape)
{
        if (!isWindowCreated())
                return;

        Cursor pointer;
        switch (shape)
        {
        case Rk::PointerShape::Arrow:
                pointer = XCreateFontCursor(display(), XC_arrow);
        break;
        case Rk::PointerShape::IBeam:
                pointer = XCreateFontCursor(display(), XC_xterm);
        break;
        default:
                return;
        };
        XDefineCursor(display(), xWindow, pointer);
}
