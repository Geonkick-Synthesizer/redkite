/**
 * File name: RkEventQueueImpl.cpp
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

#include "RkEventQueueImpl.h"
#include "RkEvent.h"
#include "RkWidget.h"

#ifdef RK_OS_WIN
#include "RkEventQueueWin.h"
#elif RK_OS_MAC
#include "RkEventQueueMac.h"
#else // X11
#incldue "RkEventQueueX.h"
#endif


RkEventQueue::RkEventQueueImpl::RkEventQueueImpl(RkEventQueue* eventQueueInterface)
        : inf_ptr{eventQueueInterface}
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

bool RkEventQueue::RkEventQueueImpl::widgetExists(RkWidget *widget)
{
	for (const auto &w : widgetList)
                if (w == widget)
                        return true;
    return false;
}

void RkEventQueue::RkEventQueueImpl::addWidget(RkWidget *widget)
{
	if (!widget || widgetExists(widget))
		return;
#if !defined(RK_OS_WIN) && !defined(RK_OS_MAC)
        // Set the display from the top window.
        if (!widget->parent() && !platformEventQueue->display())
                platformEventQueue->setDisplay(widget->getNativeWindowInfo()->display);
#endif //!defined(Rk_OS_WIN) && !defined(Rk_OS_MAC)
        widgetList.push_back(widget);
        widget->setEventQueue(inf_ptr);
}

void RkEventQueue::RkEventQueueImpl::postEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event)
{
        eventsQueue.push({widget->id(), event});
}

void RkEventQueue::RkEventQueueImpl::postEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event)
{
        eventsQueue.push({id, event});
}

void RkEventQueue::RkEventQueueImpl::postEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event)
{
        eventsQueue.push({info.window, event});
}

void RkEventQueue::RkEventQueueImpl::processEvent(RkWidget* widget, const std::shared_ptr<RkEvent> &event)
{
        widget->processEvent(event);
}

void RkEventQueue::RkEventQueueImpl::processEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event)
{
        for(auto widget : widgetList) {
                if (widget->id().id == id.id) {
                        widget->processEvent(event);
                        break;
                }
        }
}

void RkEventQueue::RkEventQueueImpl::processEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event)
{
        for(auto widget : widgetList) {
                if (widget->id().id == info.window) {
                        widget->processEvent(event);
                        break;
                }
        }
}

void RkEventQueue::RkEventQueueImpl::processEvents()
{
        platformEventQueue->getEvents(eventsQueue);
        while (!eventsQueue.empty()) {
                auto res = eventsQueue.front();
                processEvent(res.first, res.second);
                eventsQueue.pop();
        }
}
