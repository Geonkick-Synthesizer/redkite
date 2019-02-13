/**
 * File name: RkQueueX.cpp
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

#include "RkEventQueueX.h"
#include "RkLog.h"
#include "RkWidget.h"

RkEventQueueX::RkEventQueueX(Display* display)
        : xDisplay(display)
{
        RK_LOG_INFO("called");
}

RkEventQueueX::~RkEventQueueX()
{
}

bool RkEventQueueX::pending()
{
        if (xDisplay) {
                return XPending(xDisplay) > 0;
        }
        return false;
}

std::pair<RkWindowId, std::shared_ptr<RkEvent>> RkEventQueueX::nextEvent()
{
        XEvent e;
        XNextEvent(xDisplay, &e);
        RkWindowId id = rk_id_from_x11(reinterpret_cast<XAnyEvent*>(&e)->window);
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
                        auto atom = XInternAtom(xDisplay, "WM_DELETE_WINDOW", True);
                        if (static_cast<Atom>(e.xclient.data.l[0]) == atom) {
                                event = RkEvent::closeEvent();
                        }
                        break;
                }
        default:
                break;
        }

        if (event)
                return std::make_pair(id, event);

        return {};
}
