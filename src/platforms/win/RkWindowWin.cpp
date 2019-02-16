/**
 * File name: RkWindowWin.cpp
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
#include "RkWindowWin.h"

RkWindowWin::RkWindowWin(const std::shared_ptr<RkNativeWindowInfo> &parent)
        : parentWindowInfo(parent)
        , windowHandle(0)
        , windowPosition{0, 0}
        , windowSize{250, 250}
        , borderWidth{1}
        , borderColor{255, 255, 255}
        , backgroundColor{255, 255, 255}
{
}

RkWindowWin::RkWindowWin(const RkNativeWindowInfo &parent)
        : parentWindowInfo(std::make_shared<RkNativeWindowInfo>())
        , windowHandle(0)
        , windowPosition{0, 0}
        , windowSize{250, 250}
        , borderWidth{1}
        , borderColor{255, 255, 255}
        , backgroundColor{255, 255, 255}

{
        *parentWindowInfo.get() = parent;
}

RkWindowWin::~RkWindowWin()
{
        if (!hasParent()) {
        }
}

bool RkWindowWin::hasParent() const
{
        return parentWindowInfo != nullptr;
}

bool RkWindowWin::init()
{
        return true;
}

void RkWindowWin::show()
{

}

std::shared_ptr<RkNativeWindowInfo> RkWindowWin::nativeWindowInfo()
{
        if (isWindowCreated()) {
                auto info = std::make_shared<RkNativeWindowInfo>();
                info->window = windowHandle.id;
                return info;
        }

        return nullptr;
}

void RkWindowWin::setTitle(const std::string &title)
{
        //        if (!title.empty())
}

bool RkWindowWin::isWindowCreated() const
{
        return false;
}

std::pair<int, int> RkWindowWin::size() const
{
        //        if (isWindowCreated()) {
                //                return {attributes.width, attributes.height};
        //}
        return windowSize;
}

void RkWindowWin::setSize(const std::pair<int, int> &size)
{
        if (size.first > 0 && size.second > 0) {
                windowSize = size;
                //                if (isWindowCreated())
                //        XResizeWindow(display(), windowHandle, windowSize.first, windowSize.second);
        }
}

std::pair<int, int> RkWindowWin::position() const
{
        if (isWindowCreated()) {
                //                XWindowAttributes attributes;
                // XGetWindowAttributes(xDisplay, windowHandle, &attributes);
                //auto pos = std::make_pair(attributes.x, attributes.y);
                //if (pos != windowPosition)
                //        windowPosition = pos;
        }
        return windowPosition;
}

void RkWindowWin::setPosition(const std::pair<int, int> &position)
{
                windowPosition = position;
                //                if (isWindowCreated())
                //         XMoveWindow(display(), windowHandle, windowPosition.first, windowPosition.second);
}

void RkWindowWin::setBorderWidth(int width)
{
        borderWidth = width;
        //        if (isWindowCreated())
        //        XSetWindowBorderWidth(display(), windowHandle, borderWidth);
}

void RkWindowWin::setBorderColor(const std::tuple<int, int, int> &color)
{
        borderColor = color;
        //        if (isWindowCreated())
        //        XSetWindowBorder(display(), windowHandle, pixelValue(borderColor));
}

void RkWindowWin::setBackgroundColor(const std::tuple<int, int, int> &background)
{
        backgroundColor = background;
        //        if (isWindowCreated())
        //        XSetWindowBackground(display(), windowHandle, pixelValue(background));
}

RkWindowId RkWindowWin::id() const
{
        RkWindowId id;
        id.id = windowHandle.id;
        return id;
}
