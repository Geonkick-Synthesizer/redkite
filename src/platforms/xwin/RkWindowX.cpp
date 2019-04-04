/**
 * File name: RkWindowX.cpp
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

#include "RkLog.h"
#include "RkWindowX.h"
#include "RkEventQueue.h"
#include "RkCanvasInfo.h"

RkWindowX::RkWindowX(const std::shared_ptr<RkNativeWindowInfo> &parent)
        : parentWindowInfo(parent)
        , xDisplay{parent ? parent->display : nullptr}
        , screenNumber{parent ? parent->screenNumber : 0}
        , xWindow(0)
        , windowPosition{0, 0}
        , windowSize{250, 250}
        , borderWidth{0}
        , borderColor{255, 255, 255}
        , backgroundColor{255, 255, 255}
        , eventQueue{nullptr}
        , canvasInfo{nullptr}
{
}

RkWindowX::RkWindowX(const RkNativeWindowInfo &parent)
        : parentWindowInfo(std::make_shared<RkNativeWindowInfo>())
        , xDisplay{parent.display}
        , screenNumber{parent.screenNumber}
        , xWindow(0)
        , windowPosition{0, 0}
        , windowSize{250, 250}
        , borderWidth{1}
        , borderColor{255, 255, 255}
        , backgroundColor{255, 255, 255}
        , eventQueue{nullptr}
        , canvasInfo{nullptr}

{
        *parentWindowInfo.get() = parent;
}

RkWindowX::~RkWindowX()
{
        if (!hasParent() && xDisplay) {
                freeCanvasInfo();
                XCloseDisplay(xDisplay);
        }
}

bool RkWindowX::hasParent() const
{
        return parentWindowInfo != nullptr;
}

bool RkWindowX::openDisplay()
{
        xDisplay = XOpenDisplay(nullptr);
        screenNumber = DefaultScreen(xDisplay);
        return xDisplay != 0;
}

bool RkWindowX::init()
{
        if (!hasParent()) {
                if (!openDisplay()) {
                        RK_LOG_ERROR("can't open display");
                        return false;
                }
	}

        Window parent  = hasParent() ? parentWindowInfo->window : RootWindow(xDisplay, screenNumber);
        xWindow = XCreateSimpleWindow(xDisplay, parent,
                                      windowPosition.first, windowPosition.second,
                                      windowSize.first, windowSize.second, borderWidth,
                                      pixelValue(borderColor),
                                      pixelValue(backgroundColor));


        if (!xWindow) {
                RK_LOG_ERROR("can't create window");
                return false;
        }

        XSelectInput(xDisplay, xWindow, ExposureMask
                                        | KeyPressMask | KeyReleaseMask
                                        | ButtonPressMask | ButtonReleaseMask
                                        | StructureNotifyMask);

        if (!hasParent()) {
                deleteWindowAtom = XInternAtom(display(), "WM_DELETE_WINDOW", True);
                XSetWMProtocols(xDisplay, xWindow, &deleteWindowAtom, 1);
        }

        createCanvasInfo();
        return true;
}

void RkWindowX::show()
{
        if (isWindowCreated())
                XMapRaised(display(), xWindow);
}

Display* RkWindowX::display()
{
        return xDisplay;
}

std::shared_ptr<RkNativeWindowInfo> RkWindowX::nativeWindowInfo()
{
        if (isWindowCreated()) {
                auto info = std::make_shared<RkNativeWindowInfo>();
                info->display = display();
                info->screenNumber = screenNumber;
                info->window = xWindow;
                return info;
        }

        return nullptr;
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

std::pair<int, int> RkWindowX::size() const
{
        if (isWindowCreated()) {
                XWindowAttributes attributes;
                XGetWindowAttributes(xDisplay, xWindow, &attributes);
                return {attributes.width, attributes.height};
        }
        return windowSize;
}

void RkWindowX::setSize(const std::pair<int, int> &size)
{
        if (size.first > 0 && size.second > 0) {
                windowSize = size;
                if (isWindowCreated())
                        XResizeWindow(display(), xWindow, windowSize.first, windowSize.second);
        }
}

std::pair<int, int> RkWindowX::position() const
{
        if (isWindowCreated()) {
                XWindowAttributes attributes;
                XGetWindowAttributes(xDisplay, xWindow, &attributes);
                auto pos = std::make_pair(attributes.x, attributes.y);
                if (pos != windowPosition)
                        windowPosition = pos;
        }
        return windowPosition;
}

void RkWindowX::setPosition(const std::pair<int, int> &position)
{
                windowPosition = position;
                if (isWindowCreated())
                         XMoveWindow(display(), xWindow, windowPosition.first, windowPosition.second);
}

void RkWindowX::setBorderWidth(int width)
{
        borderWidth = width;
        if (isWindowCreated())
                XSetWindowBorderWidth(display(), xWindow, borderWidth);
}

unsigned long RkWindowX::pixelValue(const std::tuple<int, int, int> &color)
{
        if (!display())
                return 0;

        auto colorMap = XDefaultColormap(display(), screenNumber);
        XColor pixelColor;
        pixelColor.flags = DoRed | DoGreen | DoBlue;
        constexpr const unsigned short k = 65535 / 255;
        pixelColor.red   = k * std::get<0>(color);
        pixelColor.green = k * std::get<1>(color);
        pixelColor.blue  = k * std::get<2>(color);

        auto res = XAllocColor(display(), colorMap, &pixelColor);
        if (!res) {
                RK_LOG_ERROR("can't allocate color");
                return 0 ;
        }

        return pixelColor.pixel;
}

void RkWindowX::setBorderColor(const std::tuple<int, int, int> &color)
{
        borderColor = color;
        if (isWindowCreated())
                XSetWindowBorder(display(), xWindow, pixelValue(borderColor));
}

void RkWindowX::setBackgroundColor(const std::tuple<int, int, int> &background)
{
        backgroundColor = background;
        if (isWindowCreated())
                XSetWindowBackground(display(), xWindow, pixelValue(background));
}

RkWindowId RkWindowX::id() const
{
        RkWindowId id;
        id.id = xWindow;
        return id;
}

void RkWindowX::setEventQueue(RkEventQueue *queue)
{
        eventQueue = queue;
}

void RkWindowX::update()
{
        if (isWindowCreated())
                XClearArea(display(), xWindow, 0, 0, 0, 0, True);
}

#ifdef RK_GRAPHICS_CAIRO_BACKEND
void RkWindowX::createCanvasInfo()
{
        canvasInfo = std::make_shared<RkCanvasInfo>();
        canvasInfo->cairo_surface = cairo_xlib_surface_create(display(), xWindow,
                                                              DefaultVisual(display(), screenNumber),
                                                              size().first, size().second);
}

void RkWindowX::resizeCanvas()
{
        cairo_xlib_surface_set_size(canvasInfo->cairo_surface, size().first, size().second);
}

std::shared_ptr<RkCanvasInfo> RkWindowX::getCanvasInfo()
{
        return canvasInfo;
}

void RkWindowX::freeCanvasInfo()
{
        cairo_surface_destroy(canvasInfo->cairo_surface);
}

#else
#error No graphics backend defined
#endif // RK_GRAPHICS_CAIRO_BACKEND

