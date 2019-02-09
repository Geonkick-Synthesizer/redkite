/**
 * File name: RkWidgetXWin.cpp
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
#include "RkEvent.h"
#include "RkWidgetXWin.h"

RkWidget::RkWidgetXWin::RkWidgetXWin(const std::shared_ptr<RkNativeWindowInfo> &parent)
        : parentWindowInfo(parent),
          xDisplay(parentWindowInfo ? parent->display : nullptr),
          screenNumber(parentWindowInfo ? parent->screenNumber : 0),
          xWindow(0),
          widgetX(10),
          widgetY(10),
          widgetSize{250, 250}
{
}

RkWidget::RkWidgetXWin::~RkWidgetXWin()
{
        RK_LOG_DEBUG("delete children " << widgetChildren.size());
        for (auto child : widgetChildren) {
                RK_LOG_DEBUG("delete child " << child->title());
                delete child;
        }

        if (!hasParent() && xDisplay) {
                RK_LOG_INFO("XCloseDisplay(xDisplay)");
                XCloseDisplay(xDisplay);
        }
}

bool RkWidget::RkWidgetXWin::hasParent() const
{
        return parentWindowInfo != nullptr;
}

bool RkWidget::RkWidgetXWin::openDisplay()
{
        xDisplay = XOpenDisplay(nullptr);
        screenNumber = DefaultScreen(xDisplay);
        return xDisplay != 0;
}

bool RkWidget::RkWidgetXWin::init()
{
        if (!hasParent()) {
                if (!openDisplay()) {
                        RK_LOG_ERROR("can't open display");
                        return false;
                }
	}

        RK_LOG_DEBUG("has parent: " << hasParent());
        Window parent  = hasParent() ? parentWindowInfo->window : RootWindow(display(), screenNumber);
        std::pair<int, int> winSize = size();
        xWindow = XCreateSimpleWindow(display(), parent,
                                      x(), y(), winSize.first, winSize.second, 1,
                                      parentWindowInfo ? 123456 : BlackPixel(display(), screenNumber),
                                      parentWindowInfo ? 324567 : WhitePixel(display(), screenNumber));

        if (!xWindow) {
                RK_LOG_ERROR("can't create window");
                return false;
        }

        XSelectInput(display(), xWindow, ExposureMask
                                        | KeyPressMask | KeyReleaseMask
                                        | ButtonPressMask | ButtonReleaseMask
                                        | StructureNotifyMask);

        if (!hasParent()) {
                deleteWindowAtom = XInternAtom(display(), "WM_DELETE_WINDOW", True);
                XSetWMProtocols(display(), xWindow, &deleteWindowAtom, 1);
        }

        return true;
}

void RkWidget::RkWidgetXWin::show()
{
        if (display())
                XMapRaised(display(), xWindow);
}

std::shared_ptr<RkNativeWindowInfo> RkWidget::RkWidgetXWin::nativeWindowInfo()
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

void RkWidget::RkWidgetXWin::setTitle(const std::string &title)
{
        if (xDisplay && !title.empty())
                XStoreName(xDisplay, xWindow, title.c_str());
}

bool RkWidget::RkWidgetXWin::isWindowCreated() const
{
        return xDisplay != nullptr && xWindow;
}

std::pair<int, int> RkWidget::RkWidgetXWin::size() const
{
        return widgetSize;
}

void RkWidget::RkWidgetXWin::setSize(const std::pair<int, int> &size)
{
        if (size.first > 0 && size.second > 0) {
                widgetSize = size;
                if (isWindowCreated())
                        XResizeWindow(display(), xWindow, widgetSize.first, widgetSize.second);
        }
}

int RkWidget::RkWidgetXWin::x() const
{
        return widgetX;
}

int RkWidget::RkWidgetXWin::y() const
{
        return widgetY;
}

void RkWidget::RkWidgetXWin::setX(int x)
{
        if (x > -1) {
                widgetX = x;
                if (isWindowCreated())
                        XMoveWindow(display(), xWindow, widgetX, widgetY);
        }
}

void RkWidget::RkWidgetXWin::setY(int y)
{
        if (y > -1) {
                widgetY = y;
                if (isWindowCreated())
                        XMoveWindow(display(), xWindow, widgetX, widgetY);
        }
}

void RkWidget::RkWidgetXWin::addChild(RkWidget* child)
{
        RK_LOG_DEBUG("add child: " << child->id().id);
        widgetChildren.push_back(child);
}

RkWidget* RkWidget::RkWidgetXWin::child(const RkWindowId &id) const
{
        for (const auto &child : widgetChildren) {
                if (child->id().id == id.id) {
                        return child;
                } else {
                        auto ch = child->child(id);
                        if (ch)
                                return ch;
                }
        }

        return nullptr;
}

RkWindowId RkWidget::RkWidgetXWin::id() const
{
        RkWindowId id;
        id.id = xWindow;
        return id;
}
