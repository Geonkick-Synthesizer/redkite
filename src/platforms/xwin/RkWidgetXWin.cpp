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

RkWidget::RkWidgetXWin::RkWidgetXWin(std::shared_ptr<RkWidget::RkNativeWindowInfo> &parent)
        : parentWindowInfo(parent),
          xDisplay(parentWindowInfo ? parent->display : nullptr),
          screenNumber(parentWindowInfo ? parent->screenNumber : 0),
          xWindow(0),
          widgetX(10),
          widgetY(10)
          widgetSize{250, 250}
{
}

RkWidget::RkWidgetXWin::~RkWidgetXWin()
{
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

        Window parent  = hasParent() ? parentWindowInfo->window : RootWindow(display(), screenNumber);
        std::pair<int, int> winSize = size();
        xWindow = XCreateSimpleWindow(display(), parent,
                                      x(), y(), winSize.first, winSize.second, 1,
                                      BlackPixel(display(), screenNumber),
                                      WhitePixel(display(), screenNumber));

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

std::shared_ptr<RkWidget::RkNativeWindowInfo> RkWidget::RkWidgetXWin::nativeWindowInfo()
{
        if (isWindowCreated()) {
                audo info = std::make_shared<RkWidget::NativeWindowInfo>();
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

std::list<std::shared_ptr<RkEvent>> RkWidget::RkWidgetXWin::getEvents()
{
        std::list<std::shared_ptr<RkEvent>> events;
        XEvent e;
        while (XPending(xDisplay) > 0) {
                XNextEvent(xDisplay, &e);
                switch (e.type)
                {
                case Expose:
		        events.push_back(RkEvent::paintEvent());
                        break;
                case KeyPress:
		        events.push_back(RkEvent::keyPressEvent());
                        break;
                case KeyRelease:
		        events.push_back(RkEvent::keyReleaseEvent());
                        break;
                case ButtonPress:
		        events.push_back(RkEvent::buttonPressEvent());
                        break;
                case ButtonRelease:
		        events.push_back(RkEvent::buttonReleaseEvent());
                        break;
                case ConfigureNotify:
                        //                        if (x() != e.x || y() != e.y) {
                        //        setX(e.x);
                        //        setY(e.y);
                        //        events.push_back(RkEvent::moveEvent());
                        //}

                        //if (with() != e.with || height() != e.height()) {
                        //        setSize(e.with, e.height);
                                events.push_back(RkEvent::resizeEvent());
                                //}
                        break;
		case ClientMessage:
                        if (!xParent && (Atom)e.xclient.data.l[0] == deleteWindowAtom) {
                                RK_LOG_INFO("DestroyNotify");
                                events.push_back(RkEvent::closeEvent());
                        }
		     break;
                default:
                        break;
                }
        }
        return std::move(events);
}

bool RkWidget::RkWidgetXWin::isWindowCreated() const
{
        return display() && xWindow;
}

std::pair<int, int> RkWidget::RkWidgetXWin::size() const
{
        return widgetSize;
}

std::pair<int, int> RkWidget::RkWidgetXWin::setSize(std::pair<int, int> &size)
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
