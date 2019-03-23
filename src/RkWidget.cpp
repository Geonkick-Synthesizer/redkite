/**
 * File name: RkWidget.cpp
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

#include "RkLog.h"
#include "RkWidget.h"
#include "RkEvent.h"
#include "RkWidgetImpl.h"
#include "RkPlatform.h"
#include "RkLayout.h"

RkWidget::RkWidget(RkWidget *parent)
    : o_ptr{std::make_shared<RkWidgetImpl>(this, parent)}
{
        if (parent)
                parent->addChild(this);
}

RkWidget::RkWidget(const RkNativeWindowInfo &parent)
    : o_ptr{std::make_shared<RkWidgetImpl>(this, parent)}
{
}

RkWidget::RkWidget(RkWidget *parent, const std::shared_ptr<RkWidgetImpl> &impl)
        : o_ptr{impl}
{
        if (parent)
                parent->addChild(this);
}

RkWidget::~RkWidget()
{
}

void RkWidget::setTitle(const std::string &title)
{
        o_ptr->setTitle(title);
}

const std::string& RkWidget::title() const
{
        return o_ptr->title();
}


void RkWidget::show()
{
        o_ptr->show();
}

std::shared_ptr<RkNativeWindowInfo> RkWidget::nativeWindowInfo() const
{
        return o_ptr->nativeWindowInfo();
}

RkWindowId RkWidget::id() const
{
        return o_ptr->id();
}

bool RkWidget::isClose() const
{
        return o_ptr->isClose();
}

void RkWidget::processEvent(const std::shared_ptr<RkEvent> &event)
{
        o_ptr->processEvent(event);
}

void RkWidget::setSize(int w, int h)
{
        o_ptr->setSize({w, h});
}

void RkWidget::setSize(const std::pair<int, int> &size)
{
        o_ptr->setSize(size);
}

std::pair<int, int> RkWidget::size() const
{
        RK_LOG_DEBUG("o_ptr->size().first:" << o_ptr->size().first);
        return o_ptr->size();
}

void RkWidget::setWidth(int w)
{
        o_ptr->setSize({w, o_ptr->size().second});
}

int RkWidget::width() const
{
        RK_LOG_DEBUG("o_ptr->size().first:" << o_ptr->size().first);
        return o_ptr->size().first;
}

int RkWidget::minimumWidth() const
{
        return o_ptr->minimumWidth();
}

int RkWidget::maximumWidth() const
{
        return o_ptr->maximumWidth();
}

void RkWidget::setHeight(int h)
{
        o_ptr->setSize({o_ptr->size().first, h});
}

int RkWidget::height() const
{
        return o_ptr->size().second;
}

int RkWidget::minimumHeight() const
{
        return o_ptr->minimumHeight();
}

int RkWidget::maximumHeight() const
{
        return o_ptr->maximumHeight();
}

int RkWidget::x() const
{
        return o_ptr->position().first;
}

void RkWidget::setX(int x)
{
        o_ptr->setPosition({x, o_ptr->position().second});
}

int RkWidget::y() const
{
        return o_ptr->position().second;
}

void RkWidget::setY(int y)
{
        return o_ptr->setPosition({o_ptr->position().first, y});
}

void RkWidget::setPosition(int x, int y)
{
        o_ptr->setPosition({x, y});
}

void RkWidget::setBorderWidth(int width)
{
        o_ptr->setBorderWidth(width);
}

void RkWidget::setBorderColor(int red, int green, int blue)
{
        if (red > 255)
                red = 255;
        if (red < 0)
                red = 0;

        if (green > 255)
                green = 255;
        if (green < 0)
                green = 0;

        if (blue > 255)
                blue = 255;
        if (blue < 0)
                blue = 0;
        o_ptr->setBorderColor({red, green, blue});
}

void RkWidget::setBackgroundColor(int red, int green, int blue)
{
        if (red > 255)
                red = 255;
        if (red < 0)
                red = 0;

        if (green > 255)
                green = 255;
        if (green < 0)
                green = 0;

        if (blue > 255)
                blue = 255;
        if (blue < 0)
                blue = 0;

        o_ptr->setBackgroundColor({red, green, blue});
}

void RkWidget::setLayout(RkLayout *layout)
{
        o_ptr->setLayout(layout);
}

RkLayout* RkWidget::layout() const
{
        return o_ptr->layout();
}

RkWidget* RkWidget::parent() const
{
        return o_ptr->parent();
}

RkWidget* RkWidget::child(const RkWindowId &id) const
{
        return o_ptr->child(id);
}

void RkWidget::addChild(RkWidget* child)
{
        if (child)
               o_ptr->addChild(child);
}

void RkWidget::closeEvent(const std::shared_ptr<RkCloseEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_INFO(title() + ":called");
}

void RkWidget::keyPressEvent(const std::shared_ptr<RkKeyEvent> &event)
{
        RK_UNUSED(event);
	RK_LOG_INFO(title() + ":called");
}

void RkWidget::keyReleaseEvent(const std::shared_ptr<RkKeyEvent> &event)
{
        RK_UNUSED(event);
	RK_LOG_INFO(title() + ":called");
}

void RkWidget::mouseMoveEvent(const std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
	RK_LOG_INFO(title() + ":called");
}

void RkWidget::mouseButtonPressEvent(const std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
	RK_LOG_INFO(title() + ":called");
}

void RkWidget::mouseButtonReleaseEvent(const std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_INFO(title() + ":called");
}

void RkWidget::mouseDoubleClickEvent(const std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_INFO(title() + ":called");
}

void RkWidget::wheelEvent(const std::shared_ptr<RkWheelEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_INFO(title() + ":called");
}

void RkWidget::moveEvent(const std::shared_ptr<RkMoveEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_INFO(title() + ":called");
}

void RkWidget::resizeEvent(const std::shared_ptr<RkResizeEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_INFO(title() + ":called");
}

void RkWidget::paintEvent(const std::shared_ptr<RkPaintEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_INFO(title() + ":called");
}

void RkWidget::showEvent(const std::shared_ptr<RkShowEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::hideEvent(const std::shared_ptr<RkHideEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_INFO("called");
}

void RkWidget::setEventQueue(RkEventQueue *eventQueue)
{
        o_ptr->setEventQueue(eventQueue);
}
