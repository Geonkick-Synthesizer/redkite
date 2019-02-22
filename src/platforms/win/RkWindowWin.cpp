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
        : parentWindowInfo{parent}
        , windowHandle{{nullptr}}
        , windowPosition{0, 0}
        , windowSize{250, 250}
        , borderWidth{1}
        , borderColor{255, 255, 255}
        , backgroundColor{255, 255, 255}
        , eventQueue{nullptr}
{
}

RkWindowWin::RkWindowWin(const RkNativeWindowInfo &parent)
        : parentWindowInfo{std::make_shared<RkNativeWindowInfo>()}
        , windowHandle{{nullptr}}
        , windowPosition{0, 0}
        , windowSize{250, 250}
        , borderWidth{1}
        , borderColor{255, 255, 255}
        , backgroundColor{255, 255, 255}
        , eventQueue{nullptr}

{
        *parentWindowInfo.get() = parent;
}

RkWindowWin::~RkWindowWin()
{
}

bool RkWindowWin::hasParent() const
{
        return parentWindowInfo != nullptr;
}

bool RkWindowWin::init()
{
        windowHandle.id = CreateWindowEx(0,
                                         hasParent() ? parentWindowInfo->className.c_str() : rk_winApiClassName.c_str(),
                                         "RkWidget",
                                         !hasParent() ? WS_OVERLAPPEDWINDOW : WS_CHILD,
                                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                         !hasParent() ? nullptr : parentWindowInfo->window,
                                         nullptr,
                                         hasParent() ? parentWindowInfo->instance : rk_winApiInstance,
                                         nullptr);

        if (!windowHandle.id) {
                RK_LOG_ERROR("can't create window");
                return false;
        }

        if (eventQueue)
                SetWindowLongPtr(windowHandle.id, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(eventQueue.get()));

        return true;
}

void RkWindowWin::show()
{
        if (isWindowCreated())
                ShowWindow(windowHandle.id, SW_SHOW);
}

std::shared_ptr<RkNativeWindowInfo> RkWindowWin::nativeWindowInfo()
{
        if (isWindowCreated()) {
                auto info = std::make_shared<RkNativeWindowInfo>();
                info->className = hasParent() ? parentWindowInfo->className : rk_winApiClassName;
                info->window    = windowHandle.id;
                info->instance  = hasParent() ? parentWindowInfo->instance : rk_winApiInstance;
                return info;
        }

        return nullptr;
}

void RkWindowWin::setTitle(const std::string &title)
{
        if (isWindowCreated() && !title.empty())
                SetWindowTextA(windowHandle.id, title.c_str());
}

bool RkWindowWin::isWindowCreated() const
{
        return windowHandle.id != nullptr;
}

std::pair<int, int> RkWindowWin::size() const
{
        if (isWindowCreated()) {
                RECT rect;
                GetWindowRect(windowHandle.id, &rect);
                return {rect.right - rect.left, rect.bottom - rect.top};
        }
        return windowSize;
}

void RkWindowWin::setSize(const std::pair<int, int> &size)
{
        if (size.first > 0 && size.second > 0) {
                windowSize = size;
                if (isWindowCreated()) {
                        auto pos = position();
                        MoveWindow(windowHandle.id, pos.first, pos.second,
                                   size.first, size.second, TRUE);
                }
        }
}

std::pair<int, int> RkWindowWin::position() const
{
        if (isWindowCreated()) {
                RECT rect;
                GetWindowRect(windowHandle.id, &rect);
                return {rect.left, rect.top};
        }
        return windowPosition;
}

void RkWindowWin::setPosition(const std::pair<int, int> &position)
{
                windowPosition = position;
                if (isWindowCreated()) {
                        auto s = size();
                        MoveWindow(windowHandle.id, position.first, position.second,
                                   s.first, s.second, TRUE);
                }
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

void RkWindowWin::setEventQueue(const std::shared_ptr<RkEventQueue> &queue)
{
        eventQueue = queue;
        SetWindowLongPtr(windowHandle.id, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(eventQueue.get()));
}
