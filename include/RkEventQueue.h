/**
 * File name: RkEventQueue.h
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

#ifndef RK_EVENT_QUEUE_H
#define RK_EVENT_QUEUE_H

#include "Rk.h"

struct RkWindowId;
struct RkNativeWindowInfo;
class RkWidget;
class RkEvent;
class RkTimer;

class RK_EXPORT RkEventQueue {
 public:
        RkEventQueue();
        virtual ~RkEventQueue();

        void addWidget(RkWidget *widget);
        void removeWidget(RkWidget *widget);
        void removeWidgetEvents(RkWidget *widget);
        void postEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event);
        void postEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event);
        void postEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event);
        void processEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event);
        void processEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event);
        void processEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event);
        void processEvents();
        void postAction(const std::function<void(void)> &act);
        void processActions();
        void subscribeTimer(RkTimer *timer);
        void unsubscribeTimer(RkTimer *timer);
        void processTimers();
        // Process all: events, actions and timers.
        void processQueue();
        void clearEvents(const RkWidget *widget);
        void clearAllEvents();

 protected:
        RK_DECLARE_IMPL(RkEventQueue)
        RkEventQueue(const std::shared_ptr<RkEventQueueImpl> &impl);

 private:
        RK_DISABLE_COPY(RkEventQueue)
        RK_DISABLE_MOVE(RkEventQueue)
};

#endif // RK_EVENT_QUEUE_H
