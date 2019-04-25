/**
 * File name: RkEventQueueImpl.h
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

#ifndef RK_EVENT_QUEUE_IMPL_H
#define RK_EVENT_QUEUE_IMPL_H

#include "RkEventQueue.h"
#include "RkPlatform.h"

#include <list>
#include <queue>
#include <mutex>

#ifdef RK_OS_WIN
        class RkEventQueueWin;
#elif RK_OS_MAC
        class RkEventQueueMac;
#else // X11
        class RkEventQueueX;
#endif


class RkEventQueue::RkEventQueueImpl {
 public:
        explicit RkEventQueueImpl(RkEventQueue* eventQueueInterface);
        RkEventQueueImpl(const RkEventQueue &other) = delete;
        RkEventQueueImpl& operator=(const RkEventQueueImpl &other) = delete;
        RkEventQueueImpl(RkEventQueueImpl &&other) = delete;
        RkEventQueueImpl& operator=(RkEventQueueImpl &&other) = delete;
        virtual ~RkEventQueueImpl();

        bool widgetExists(RkWidget *widget);
        void addWidget(RkWidget *widget);
        void removeWidget(RkWidget *widget);
        void postEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event);
        void postEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event);
        void postEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event);
        void processEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event);
        void processEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event);
        void processEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event);
        void processEvents();
        void postAction(const std::function<void(void)> &act);
        void processActions();

 private:
        RK_DECALRE_INTERFACE_PTR(RkEventQueue)
        std::list<RkWidget*> widgetList;
        std::queue<std::pair<RkWindowId, std::shared_ptr<RkEvent>>> eventsQueue;
        std::vector<std::function<void(void)>> actionsQueue;
        std::mutex actionsQueueMutex;

#ifdef RK_OS_WIN
        std::unique_ptr<RkEventQueueWin> platformEventQueue;
#elif RK_OS_MAC
        std::unique_ptr<RkEventQueueMac> platformEventQueue;
#else // X11
        std::unique_ptr<RkEventQueueX> platformEventQueue;
#endif
};

#endif // RK_EVENT_QUEUE_IMPL_H
