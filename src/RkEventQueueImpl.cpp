/**
 * File name: RkEventQueueImpl.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://iuriepage.wordpress.com>
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

#include "RkWidget.h"
#include "RkEventQueueImpl.h"
#include "RkTimer.h"
#include "RkAction.h"

#ifdef RK_OS_WIN
#include "RkEventQueueWin.h"
#elif RK_OS_MAC
#include "RkEventQueueMac.h"
#else // X11
#include "RkEventQueueX.h"
#endif


RkEventQueue::RkEventQueueImpl::RkEventQueueImpl(RkEventQueue* interface)
        : inf_ptr{interface}
#ifdef RK_OS_WIN
        , platformEventQueue{std::make_unique<RkEventQueueWin>()}
#elif RK_OS_MAC
        , platformEventQueue{std::make_unique<RkEventQueueMac>()}
#else // X11
        , platformEventQueue{std::make_unique<RkEventQueueX>()}
#endif
{
}

RkEventQueue::RkEventQueueImpl::~RkEventQueueImpl()
{
}

bool RkEventQueue::RkEventQueueImpl::objectExists(RkObject *obj) const
{
        return objectsList.find(obj) != objectsList.end();
}

void RkEventQueue::RkEventQueueImpl::addObject(RkObject *obj)
{
        if (obj) {
                if (!obj->eventQueue())
                        obj->setEventQueue(inf_ptr);
                objectsList.insert(obj);
        }
}

void RkEventQueue::RkEventQueueImpl::removeObject(RkObject *obj)
{
        if (objectsList.find(obj) != objectsList.end())
                objectsList.erase(obj);
}

// void RkEventQueue::RkEventQueueImpl::addWidget(RkWidget *widget)
// {
// 	if (!widget || widgetExists(widget))
// 		return;
// #if !defined(RK_OS_WIN) && !defined(RK_OS_MAC)
//         // Set the display from the top window.
//         if (!widget->parent() && !platformEventQueue->display())
//                 platformEventQueue->setDisplay(widget->nativeWindowInfo()->display);
//         windowIdsMap.insert({widget->id().id, widget});
// #else
// #error platform not implemented
// #endif
//         widgetList.push_back(widget);
//         if (!widget->eventQueue())
//                 widget->setEventQueue(inf_ptr);
// }

// RkWidget* RkEventQueue::RkEventQueueImpl::findWidget(const RkWindowId &id) const
// {
// #if !defined(RK_OS_WIN) && !defined(RK_OS_MAC)
//         auto it = windowIdsMap.find(id.id);
// #else
// #error platform not implemented
// #endif
//         if (it != windowIdsMap.end())
//                 return it->second;

//         return nullptr;
// }

// RkWidget* RkEventQueue::RkEventQueueImpl::findWidget(const RkNativeWindowInfo &info) const
// {
// #if !defined(RK_OS_WIN) && !defined(RK_OS_MAC)
//         auto it = windowIdsMap.find(info.window);
// #else
// #error platform not implemented
// #endif
//         if (it != windowIdsMap.end())
//                 return it->second;

//         return nullptr;
// }

// void RkEventQueue::RkEventQueueImpl::removeWidget(RkWidget *widget)
// {
//         for (auto it = widgetList.begin(); it != widgetList.end(); ++it) {
//                 if (*it == widget) {
//                        widgetList.erase(it);
// #if !defined(RK_OS_WIN) && !defined(RK_OS_MAC)
//                        windowIdsMap.erase((*it)->id().id);
// #else
// #error platform not implemented
// #endif
//                        return;
//                 }
//         }
// }

void RkEventQueue::RkEventQueueImpl::postEvent(RkObject *obj, std::unique_ptr<RkEvent> event)
{
        eventsQueue.push_back({obj, std::move(event)});
}

// void RkEventQueue::RkEventQueueImpl::postEvent(const RkWindowId &id,
//                                                const std::shared_ptr<RkEvent> &event)
// {
//         eventsQueue.push_back({id, event});
// }

// void RkEventQueue::RkEventQueueImpl::postEvent(const RkNativeWindowInfo &info,
//                                                const std::shared_ptr<RkEvent> &event)
// {
//         //        eventsQueue.push({info.window, event});
// }

void RkEventQueue::RkEventQueueImpl::processEvent(RkObject *obj, RkEvent *event)
{
        obj->event(event);
}

// void RkEventQueue::RkEventQueueImpl::processEvent(const RkWindowId &id,
//                                                   const std::shared_ptr<RkEvent> &event)
// {
//         if (auto widget = findWidget(id); widget)
//                 widget->processEvent(event);
// }

// void RkEventQueue::RkEventQueueImpl::processEvent(const RkNativeWindowInfo &info,
//                                                   const std::shared_ptr<RkEvent> &event)
// {
//         if (auto widget = findWidget(info); widget)
//                 widget->processEvent(event);
// }

void RkEventQueue::RkEventQueueImpl::processEvents()
{
        //        platformEventQueue->getEvents(eventsQueue);
        decltype(eventsQueue) queue = std::move(eventsQueue);
        eventsQueue.clear();
        for (const auto &e: queue)
                processEvent(e.first, e.second.get());
}

void RkEventQueue::RkEventQueueImpl::postAction(std::unique_ptr<RkAction> act)
{
        std::lock_guard<std::mutex> lock(actionsQueueMutex);
        actionsQueue.push_back(std::move(act));
}

void RkEventQueue::RkEventQueueImpl::processActions()
{
        decltype(actionsQueue) q;
        {
                std::lock_guard<std::mutex> lock(actionsQueueMutex);
                q = std::move(actionsQueue);
        }

        for(const auto &act: q)
                act->call();
}

void RkEventQueue::RkEventQueueImpl::subscribeTimer(RkTimer *timer)
{
        timersList.insert(timer);
}

void RkEventQueue::RkEventQueueImpl::unsubscribeTimer(RkTimer *timer)
{
        if (timersList.find(timer) != timersList.end())
                timersList.erase(timer);
}

void RkEventQueue::RkEventQueueImpl::processTimers()
{
        for (const auto &timer: timersList) {
                if (timer->started() && timer->isTimeout())
                        timer->callTimeout();
        }
}

void RkEventQueue::RkEventQueueImpl::clearEvents(const RkObject *obj)
{
        if (!obj)
                return;

        eventsQueue.erase(std::remove_if(eventsQueue.begin(),
                                         eventsQueue.end(),
                                         [obj](std::pair<RkObject*, std::unique_ptr<RkEvent>> &ev) {
                                                 return ev.first == obj;
                                        })
                          , eventsQueue.end());
}

void RkEventQueue::RkEventQueueImpl::clearActions(const RkObject *obj)
{
        if (!obj)
                return;

        std::lock_guard<std::mutex> lock(actionsQueueMutex);
        actionsQueue.erase(std::remove_if(actionsQueue.begin(), actionsQueue.end(),
                                          [obj](const std::unique_ptr<RkAction> &act)
                                          {
                                                  return act->object() && act->object() == obj;
                                          })
                           , actionsQueue.end());
}

