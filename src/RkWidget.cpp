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
    : widgetImpl{std::make_unique<RkWidgetImpl>(parent)}
{
        if (parent)
                parent->addChild(this);
}

RkWidget::RkWidget(const std::shared_ptr<RkNativeWindowInfo> &parent)
        : widgetImpl{std::make_unique<RkWidgetImpl>(parent)}
{
}

RkWidget::~RkWidget()
{
}

void RkWidget::setTitle(const std::string &title)
{
        RK_IMPL(RkWidget)->setTitle(title);
}

const std::string& RkWidget::title() const
{
        return RK_IMPL(RkWidget)->title();
}


void RkWidget::show()
{
        RK_IMPL(RkWidget)->show();
}

std::shared_ptr<RkNativeWindowInfo> RkWidget::nativeWindowInfo() const
{
        return RK_IMPL(RkWidget)->nativeWindowInfo();
}

RkWindowId RkWidget::id() const
{
        return RK_IMPL(RkWidget)->id();
}

bool RkWidget::isClose() const
{
        return RK_IMPL(RkWidget)->isClose();
}

void RkWidget::processEvent(const std::shared_ptr<RkEvent> &event)
{
}

void RkWidget::setSize(int x, int y)
{
        RK_IMPL(RkWidget)->setSize({x, y});
}

void RkWidget::setSize(const std::pair<int, int> &size)
{
        widgetImpl->setSize(size);
}

std::pair<int, int> RkWidget::size() const
{
        return std::move(RK_IMPL(RkWidget)->size());
}

void RkWidget::setWidth(int w)
{
        widgetImpl->setSize({w, RK_IMPL(RkWidget)->size().second});
}

int RkWidget::width() const
{
        return widgetImpl->size().first;
}

void RkWidget::setHeight(int h)
{
        widgetImpl->setSize({RK_IMPL(RkWidget)->size().first, h});
}

int RkWidget::height() const
{
        return RK_IMPL(RkWidget)->size().second;
}

int RkWidget::x() const
{
        return RK_IMPL(RkWidget)->x();
}

void RkWidget::setX(int x)
{
        RK_IMPL(RkWidget)->setX(x);
}

int RkWidget::y() const
{
        return RK_IMPL(RkWidget)->y();
}

void RkWidget::setY(int y)
{
        return RK_IMPL(RkWidget)->setY(y);
}

void RkWidget::setBackgroundColor(int r, int g, int b)
{
        RK_IMPL(RkWidget)->setBackgroundColor(r, g, b);
}

RkWidget* RkWidget::child(const RkWindowId &id) const
{
        return RK_IMPL(RkWidget)->child(id);
}

void RkWidget::addChild(RkWidget* child)
{
        if (child)
               RK_IMPL(RkWidget)->addChild(child);
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
