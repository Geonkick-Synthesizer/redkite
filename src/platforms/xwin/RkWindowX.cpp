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

RkWindowX::RkWindowX(const std::shared_ptr<RkNativeWindowInfo> &parent)
        : parentWindowInfo(parent)
        , xDisplay(parent ? parent->display : nullptr)
        , screenNumber(parentWindowInfo ? parent->screenNumber : 0)
        , xWindow(0)
        , windowPosition{0, 0}
        , windowSize{250, 250}
{
}

RkWindowX::RkWindowX(const RkNativeWindowInfo &parent)
        : parentWindowInfo(std::make_shared<RkNativeWindowInfo>())
{
        *parentWindowInfo.get() = parent;
}

RkWindowX::~RkWindowX()
{
        if (!hasParent() && xDisplay) {
                RK_LOG_INFO("XCloseDisplay(xDisplay)");
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
                RK_LOG_INFO("open display");
                if (!openDisplay()) {
                        RK_LOG_ERROR("can't open display");
                        return false;
                }
	}

        Window parent  = hasParent() ? parentWindowInfo->window : RootWindow(xDisplay, screenNumber);
        xWindow = XCreateSimpleWindow(xDisplay, parent,
                                      windowPosition.first, windowPosition.second,
                                      windowSize.first, windowSize.second, 1,
                                      parentWindowInfo ? 123456 : BlackPixel(display(), screenNumber),
                                      parentWindowInfo ? 324567 : WhitePixel(display(), screenNumber));

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
        RK_LOG_INFO("here6");
        return true;
}

void RkWindowX::show()
{
        if (display())
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
                return std::move(info);
        }

        return nullptr;
}

void RkWindowX::setTitle(const std::string &title)
{
        if (xDisplay && !title.empty())
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

void RkWindowX::setBackgroundColor(const std::tuple<int, int, int, int> &background)
{
        if (isWindowCreated()) {
                auto colorMap = XDefaultColormap(display(), screenNumber);
                XColor color;
                color.flags = DoRed | DoGreen | DoBlue;
                color.red   = (65535 / 255) * std::get<0>(background);
                color.green = (65535 / 255) * std::get<1>(background);
                color.blue  = (65535 / 255) * std::get<2>(background);
                auto res = XAllocColor(display(), colorMap, &color);
                if (!res) {
                        RK_LOG_ERROR("can't allocate color");
                        return;
                }
                else {
                        XSetWindowBackground(display(), xWindow, color.pixel);
                }
        }
}

RkWindowId RkWindowX::id() const
{
        RkWindowId id;
        id.id = xWindow;
        return id;
}
