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

RkEventQueueX::RkEventQueueX()
        : xDisplay(nullptr)
{
        RK_LOG_INFO("called");
}

RkEventQueueX::~RkEventQueueX()
{
}

bool RkEventQueueX::pending()
{
        if (xDisplay)
                return XPending(xDisplay) > 0;
        return false;
}

void RkEventQueueX::setDisplay(Display *display)
{
        xDisplay = display;
}

Display* RkEventQueueX::display() const
{
        return xDisplay;
}

void RkEventQueueX::getEvents(std::queue<std::pair<RkWindowId, std::shared_ptr<RkEvent>>> &eventsQueue)
{
        while (pending()) {
                XEvent e;
                XNextEvent(xDisplay, &e);
                RkWindowId id = rk_id_from_x11(reinterpret_cast<XAnyEvent*>(&e)->window);
                std::shared_ptr<RkEvent> event = nullptr;
                switch (e.type)
                {
                case Expose:
                        if (reinterpret_cast<XExposeEvent*>(&e)->count == 0)
                                event = std::make_shared<RkPaintEvent>();
                break;
                case KeyPress:
                        event = std::make_shared<RkKeyEvent>();
                        break;
                case KeyRelease:
                        event = std::make_shared<RkKeyEvent>();
                        event->setType(RkEvent::Type::KeyReleased);
                        break;
                case ButtonPress:
                        event = processButtonPressEvent(&e);
                        break;
                case ButtonRelease:
                        event = std::make_shared<RkMouseEvent>();
                        event->setType(RkEvent::Type::MouseButtonRelease);
                        break;
                case MotionNotify:
                        event = processMouseMove(&e);
                        break;
                case ConfigureNotify:
                        event = std::make_shared<RkResizeEvent>();
                        break;
                case ClientMessage:
                {
                        auto atom = XInternAtom(xDisplay, "WM_DELETE_WINDOW", True);
                        if (static_cast<Atom>(e.xclient.data.l[0]) == atom)
                                event = std::make_shared<RkCloseEvent>();
                        break;
                }
                default:
                        break;
                }

                if (event) {
                        eventsQueue.push({id, event});
                }
        }
}

std::shared_ptr<RkEvent> RkEventQueueX::processButtonPressEvent(XEvent *e)
{
        auto buttonEvent = reinterpret_cast<XButtonEvent*>(e);
        auto mouseEvent = std::make_shared<RkMouseEvent>();
        mouseEvent->setTime(std::chrono::system_clock::time_point(std::chrono::milliseconds(buttonEvent->time)));
        mouseEvent->setX(buttonEvent->x);
        mouseEvent->setY(buttonEvent->y);

        switch (buttonEvent->button)
        {
        case Button1:
                mouseEvent->setButton(RkMouseEvent::ButtonType::Left);
                break;
        case Button2:
                mouseEvent->setButton(RkMouseEvent::ButtonType::Middle);
                break;
        case Button3:
                mouseEvent->setButton(RkMouseEvent::ButtonType::Right);
                break;
        case Button4:
                mouseEvent->setButton(RkMouseEvent::ButtonType::WeelUp);
                break;
        case Button5:
                mouseEvent->setButton(RkMouseEvent::ButtonType::WeelDown);
                break;
        default:
                mouseEvent->setButton(RkMouseEvent::ButtonType::Unknown);
        }

        auto diff = mouseEvent->time().time_since_epoch() - lastTimePressed.time_since_epoch();
        if (std::chrono::duration_cast<std::chrono::microseconds>(diff).count() < 300000)
                mouseEvent->setType(RkEvent::Type::MouseDoubleClick);
        lastTimePressed = mouseEvent->time();

        return mouseEvent;
}

std::shared_ptr<RkEvent> RkEventQueueX::processMouseMove(XEvent *e)
{
        auto buttonEvent = reinterpret_cast<XMotionEvent*>(e);
        auto mouseEvent = std::make_shared<RkMouseEvent>();
        mouseEvent->setTime(std::chrono::system_clock::time_point(std::chrono::milliseconds(buttonEvent->time)));
        mouseEvent->setType(RkEvent::Type::MouseMove);
        mouseEvent->setX(buttonEvent->x);
        mouseEvent->setY(buttonEvent->y);
        return mouseEvent;
}

