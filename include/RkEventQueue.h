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

class RkEventQueue {
 public:
        RkEventQueue();
        virtual ~RkEventQueue();
        RkEventQueue(const RkEventQueue &other) = delete;
        RkEventQueue& operator=(const RkEventQueue &other) = delete;
        RkEventQueue(RkEventQueue &&other) = delete;
        RkEventQueue& operator=(RkEventQueue &&other) = delete;

        void addWidget(RkWidget *widget);
        void postEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event);
        void postEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event);
        void postEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event);
        void processEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event);
        void processEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event);
        void processEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event);
        void processEvents();

        protected:
                RK_DECLARE_IMPL(RkEventQueue)
                RkEventQueue(const std::shared_ptr<RkEventQueueImpl> &impl);
};

#endif // RK_EVENT_QUEUE_H
