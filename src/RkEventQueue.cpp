/**
 * File name: RkEventQueue.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://quamplex.com>
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

void RkEventQueue::addWidget(RkWidget *widget)
{
        o_ptr->addWidget(widget);
}

void RkEventQueue::removeWidget(RkWidget *widget)
{
        o_ptr->removeWidget(widget);
}

void RkEventQueue::postEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event)
{
        o_ptr->postEvent(widget, event);
}

void RkEventQueue::postEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event)
{
        o_ptr->postEvent(id, event);
}

void RkEventQueue::postEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event)
{
        o_ptr->postEvent(info, event);
}

void RkEventQueue::processEvent(RkWidget *widget, const std::shared_ptr<RkEvent> &event)
{
	o_ptr->processEvent(widget, event);
}

void RkEventQueue::processEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event)
{
	o_ptr->processEvent(id, event);
}

void RkEventQueue::processEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event)
{
	o_ptr->processEvent(info, event);
}

void RkEventQueue::processEvents()
{
        o_ptr->processEvents();
}

void RkEventQueue::postAction(const std::function<void(void)> &act)
{
        o_ptr->postAction(act);
}

void RkEventQueue::processActions()
{
        o_ptr->processActions();
}
