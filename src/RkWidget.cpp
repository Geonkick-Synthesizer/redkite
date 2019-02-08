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

RkWidget::RkWidget(RkWidget *parent)
    : o_ptr{std::make_unique<RkWidgetImpl>(this, parent)}
{
        if (parent)
                parent->addChild(this);
}

RkWidget::RkWidget(const std::shared_ptr<RkNativeWindowInfo> &parent)
    : o_ptr{std::make_unique<RkWidgetImpl>(this, parent)}
{
}

RkWidget::RkWidget(RkWidget *parent, RkWidgetImpl &impl)
    : o_ptr{&impl}
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
}

void RkWidget::setSize(int x, int y)
{
        o_ptr->setSize({x, y});
}

void RkWidget::setSize(const std::pair<int, int> &size)
{
        o_ptr->setSize(size);
}

std::pair<int, int> RkWidget::size() const
{
        return std::move(o_ptr->size());
}

void RkWidget::setWidth(int w)
{
        o_ptr->setSize({w, o_ptr->size().second});
}

int RkWidget::width() const
{
        return o_ptr->size().first;
}

void RkWidget::setHeight(int h)
{
        o_ptr->setSize({o_ptr->size().first, h});
}

int RkWidget::height() const
{
        return o_ptr->size().second;
}

int RkWidget::x() const
{
        return o_ptr->x();
}

void RkWidget::setX(int x)
{
        o_ptr->setX(x);
}

int RkWidget::y() const
{
        return o_ptr->y();
}

void RkWidget::setY(int y)
{
        return o_ptr->setY(y);
}

void RkWidget::setBackgroundColor(int r, int g, int b)
{
        o_ptr->setBackgroundColor(r, g, b);
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
