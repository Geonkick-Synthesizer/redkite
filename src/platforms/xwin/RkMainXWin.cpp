/**
 * File name: RkMainXwin.cpp
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

#include "RkEvent.h"
#include "RkMainXWin.h"
#include "RkLog.h"
#include "RkWidget.h"

RkMain::RkMainXWin::RkMainXWin()
  : topWindow(nullptr)
{
        RK_LOG_INFO("called");
}

RkMain::RkMainXWin::~RkMainXWin()
{
}

bool RkMain::RkMainXWin::setTopLevelWindow(RkWidget* widget)
{
      if (topWindow)
              return false;

      topWindow = widget;
      return true;
}

RkWidget* RkMain::RkMainXWin::topLevelWindow(void)
{
      return topWindow;
}

void RkMain::RkMainXWin::processEvents()
{
        XEvent e;
        Display* display = topLevelWindow()->nativeWindowInfo()->display;
        while (XPending(display) > 0) {
                XNextEvent(display, &e);
                auto id = reinterpret_cast<XAnyEvent*>(&e)->window;
                RkWidget* widget = nullptr;
                if (topLevelWindow()->id().id == id)
                        widget = topLevelWindow();
                else
                        widget = topLevelWindow()->child(rk_id_from_x11(id));
                if (!widget) {
                        RK_LOG_ERROR("can't find widget with ID: " << id);
                        continue;
                }

                std::shared_ptr<RkEvent> event = nullptr;
                switch (e.type)
                {
                case Expose:
                        event = RkEvent::paintEvent();
                        break;
                case KeyPress:
                        event = RkEvent::keyPressEvent();
                        break;
                case KeyRelease:
                        event = RkEvent::keyReleaseEvent();
                        break;
                case ButtonPress:
                        event = RkEvent::buttonPressEvent();
                        break;
                case ButtonRelease:
                        event = RkEvent::buttonReleaseEvent();
                        break;
                case ConfigureNotify:
                        event = RkEvent::resizeEvent();
                        break;
                case ClientMessage:
                {
                        auto atom = XInternAtom(display, "WM_DELETE_WINDOW", True);
                        if (static_cast<Atom>(e.xclient.data.l[0]) == atom) {
                                event = RkEvent::closeEvent();
                        }
                        break;
                }
                default:
                        break;
                }

                if (event && widget)
                        widget->processEvent(event);
        }
}

int RkMain::RkMainXWin::exec(bool block)
{
        if (!topLevelWindow()) {
                RK_LOG_ERROR("top window not defined");
		return 1;
	}

        if (!block) {
                processEvents();
        } else {
                for (; block ;) {
                        processEvents();
                        if (topLevelWindow()->isClose())
                                break;
                        std::this_thread::sleep_for(std::chrono::milliseconds(15));
                }
        }

        return 0;
}
