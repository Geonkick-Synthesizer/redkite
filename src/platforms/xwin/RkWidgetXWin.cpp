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

RkWidget::RkWidgetXWin::RkWidgetXWin(RkNativeWindow parent)
        : xParent(parent),
          xDisplay(nullptr),
          screenNumber(0)
{
}

RkWidget::RkWidgetXWin::~RkWidgetXWin()
{
        if (!xParent && xDisplay)
                XCloseDisplay(xDisplay);
}

bool RkWidget::RkWidgetXWin::init()
{
        xDisplay = XOpenDisplay(nullptr);
	if (!xDisplay) {
	        RK_LOG_ERROR("can't open display");
		return false;
	}

        screenNumber = DefaultScreen(xDisplay);
        if (xParent) {
                XWindowAttributes attributes;
                XGetWindowAttributes(xDisplay, static_cast<Window>(xParent), &attributes);
                screenNumber = XScreenCount(xDisplay);
                xWindow = XCreateSimpleWindow(xDisplay, static_cast<Window>(xParent),
                                              10, 10, 250, 250, 1,
                                              BlackPixel(xDisplay, screenNumber),
                                              WhitePixel(xDisplay, screenNumber));
        } else {
                if (!xDisplay) {
                                RK_LOG_ERROR("screen is not defined");
                                return false;
                }
                xWindow = XCreateSimpleWindow(xDisplay, RootWindow(xDisplay, screenNumber),
                                              10, 10, 250, 250, 1,
                                              BlackPixel(xDisplay, screenNumber),
                                              WhitePixel(xDisplay, screenNumber));
        }

        XSelectInput(xDisplay, xWindow, ExposureMask | KeyPressMask);
        return true;
}

void RkWidget::RkWidgetXWin::show()
{
        if (xDisplay)
                XMapRaised(xDisplay, xWindow);
}

RkWidget::RkNativeWindow RkWidget::RkWidgetXWin::getWindow()
{
        return static_cast<RkWidget::RkNativeWindow>(xWindow);
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
                        break;
                case KeyPress:
                        break;
                default:
                        break;
                }
        }
        return std::move(events);
}


