/**
 * File name: RkEventQueue.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://geontime.com>
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

#include "RkEventQueue.h"
#include "RkEventQueueImpl.h"

RkEventQueue::RkEventQueue()
        : o_ptr{std::make_shared<RkEventQueueImpl>(this)}
{
}

RkEventQueue::RkEventQueue(const std::shared_ptr<RkEventQueueImpl> &impl)
        : o_ptr{impl}
{
}

RkEventQueue::~RkEventQueue()
{
}

void RkEventQueue::addObject(RkObject *obj)
{
        o_ptr->addObject(obj);
}

void RkEventQueue::removeObject(RkObject *obj)
{
        o_ptr->removeObject(obj);
}

void RkEventQueue::postEvent(RkObject *obj, std::unique_ptr<RkEvent> event)
{
        o_ptr->postEvent(object, std::move(event));
}

void RkEventQueue::postAction(std::unique_ptr<RkAction> &act)
{
        o_ptr->postAction(std::move(act));
}

void RkEventQueue::subscribeTimer(RkTimer *timer)
{
        if (timer)
                o_ptr->subscribeTimer(timer);
}

void RkEventQueue::unsubscribeTimer(RkTimer *timer)
{
        if (timer)
                o_ptr->unsubscribeTimer(timer);
}

void RkEventQueue::processEvents()
{
        o_ptr->processEvents();
}

void RkEventQueue::processActions()
{
        o_ptr->processActions();
}

void RkEventQueue::processTimers()
{
        o_ptr->processTimers();
}

void RkEventQueue::processQueue()
{
        // The order is important.
        processTimers();
        processActions();
        processEvents();
}

// void RkEventQueue::postEvent(const RkWindowId &id,
//                              const std::shared_ptr<RkEvent> &event)
// {
//         o_ptr->postEvent(id, event);
// }

// void RkEventQueue::postEvent(const RkNativeWindowInfo &info,
//                              const std::shared_ptr<RkEvent> &event)
// {
//         o_ptr->postEvent(info, event);
// }

// void RkEventQueue::processEvent(RkObject *obj, RkEvent *event)
// {
// 	o_ptr->processEvent(obj, event);
// }

// void RkEventQueue::processEvent(const RkWindowId &id,
//                                 const std::shared_ptr<RkEvent> &event)
// {
// 	o_ptr->processEvent(id, event);
// }

// void RkEventQueue::processEvent(const RkNativeWindowInfo &info,
//                                 const std::shared_ptr<RkEvent> &event)
// {
// 	o_ptr->processEvent(info, event);
// }

void RkEventQueue::clearObjectEvents(const RkObject *obj)
{
        if (obj)
                o_ptr->clearEvents(obj);
}

void RkEventQueue::clearObjectActions(const RkObject *act)
{
        if (act)
                o_ptr->clearActions(act);
}

void RkEventQueue::clearEvents()
{
        o_ptr->clearEvents(nullptr);
}

void RkEventQueue::clearActions()
{
        o_ptr->clearActions(nullptr);
}

void RkEventQueue::clearTimers()
{
        o_ptr->clearTimers();
}

void RkEventQueue::clearQueue()
{
        clearEvents();
        clearActions();
        clearTimers();
}
