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

#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>

RkEventQueueX::RkEventQueueX()
        : xDisplay(nullptr)
        , keyModifiers{0}
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

void RkEventQueueX::getEvents(std::vector<std::pair<RkWindowId, std::shared_ptr<RkEvent>>> &eventsQueue)
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
                        event = processKeyEvent(&e);
                        break;
                case KeyRelease:
                        event = processKeyEvent(&e);
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

                if (event)
                        eventsQueue.push_back({id, event});
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

std::shared_ptr<RkEvent> RkEventQueueX::processKeyEvent(XEvent *e)
{
        auto event = std::make_shared<RkKeyEvent>();
        event->setType(e->type == KeyPress ? RkEvent::Type::KeyPressed : RkEvent::Type::KeyReleased);
        auto keyCode = XkbKeycodeToKeysym(xDisplay, reinterpret_cast<XKeyEvent*>(e)->keycode, 0, 1);
        event->setKey(fromKeysym(keyCode));
        updateModifiers(event->key(), event->type());
        if (keyModifiers != static_cast<int>(Rk::KeyModifiers::NoModifier))
                event->setModifiers(keyModifiers);
        return event;
}

void RkEventQueueX::updateModifiers(Rk::Key key, RkEvent::Type type)
{
        if (key == Rk::Key::Key_Shift_Left || key == Rk::Key::Key_Shift_Right)
        {
                if (type == RkEvent::Type::KeyPressed)
                        keyModifiers |= static_cast<int>(key);
                else
                        keyModifiers &= ~static_cast<int>(key);
        }
        RK_LOG_DEBUG("modifyier: " << keyModifiers);
}

Rk::Key RkEventQueueX::fromKeysym(int keycode)
{
        if (static_cast<int>(Rk::Key::Key_A) <= keycode && keycode <= static_cast<int>(Rk::Key::Key_Z))
                return static_cast<Rk::Key>(keycode);

        switch (keycode)
        {
        // Key modifiers
        case XK_Shift_L: return Rk::Key::Key_Shift_Left;
        case XK_Shift_R: return Rk::Key::Key_Shift_Right;
        case XK_Control_L: return Rk::Key::Key_Control_Left;
        case XK_Control_R: return Rk::Key::Key_Control_Right;
        case XK_Caps_Lock: return Rk::Key::Key_Caps_Lock;
        case XK_Shift_Lock: return Rk::Key::Key_Shift_Lock;
        case XK_Meta_L: return Rk::Key::Key_Meta_Left;
        case XK_Meta_R: return Rk::Key::Key_Meta_Right;
        case XK_Alt_L: return Rk::Key::Key_Alt_Left;
        case XK_Alt_R: return Rk::Key::Key_Alt_Right;
        case XK_Super_L: return Rk::Key::Key_Super_Left;
        case XK_Super_R: return Rk::Key::Key_Super_Right;
        case XK_Hyper_L: return Rk::Key::Key_Hyper_Left;
        case XK_Hyper_R: return Rk::Key::Key_Hyper_Right;

        // Pointer control keys
        case XK_Home: return Key_Home;                         0xff50
        case XK_Left: Key_Left                         0xff51  /* Move left, left arrow */
        case XK_Up:   return Key_Up                         0xff52  /* Move up, up arrow */
        case XK_Right: return Key_Right;
        case XK_Down:  return Key_down                        0xff54  /* Move down, down arrow */
        case XK_Prior:                         0xff55  /* Prior, previous */
        case XK_Page_Up:                       0xff55
        case XK_Next:                          0xff56  /* Next */
        case XK_Page_Down:                     0xff56
        case XK_End:                           0xff57  /* EOL */
        case XK_Begin:                         0xff58  /* BOL */
        default: return Rk::Key::Key_None;
        }
}
