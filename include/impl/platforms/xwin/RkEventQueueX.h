/**
 * File name: RkQueueX.h
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

#ifndef RK_EVENT_QUEUE_X_H
#define RK_EVENT_QUEUE_X_H

#include "RkEvent.h"
#include "RkPlatform.h"

#include <queue>

class RkEvent;
class RkObject;

class RkEventQueueX
{
 public:
        RkEventQueueX();
	~RkEventQueueX();
        RkEventQueueX(const RkEventQueueX &other) = delete;
        RkEventQueueX& operator=(const RkEventQueueX &other) = delete;
        RkEventQueueX(RkEventQueueX &&other) = delete;
        RkEventQueueX& operator=(RkEventQueueX &&other) = delete;
        bool pending();
        void setDisplay(Display *display);
        Display* display() const;
        std::vector<std::pair<WindowsId, std::unique_ptr<RkEvent>>> getEvents() const;

 protected:
        std::shared_ptr<RkEvent> processButtonPressEvent(XEvent *e);
        std::shared_ptr<RkEvent> processMouseMove(XEvent *e);
        std::shared_ptr<RkEvent> processKeyEvent(XEvent *e);
        std::shared_ptr<RkEvent> processFocusEvent(XEvent *e);
        void updateModifiers(Rk::Key key, RkEvent::Type type);
        Rk::Key fromKeysym(int keycode);

 private:
       Display* xDisplay;
       std::chrono::system_clock::time_point lastTimePressed;
       int keyModifiers;
};

#endif // RK_EVENT_QUEUE_X_H
