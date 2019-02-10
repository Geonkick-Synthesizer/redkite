/**
 * File name: RkWidget.cpp
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

#include "RkLog.h"
#include "RkWidget.h"
#include "RkEvent.h"

#ifdef RK_WIN_OS
#elif RK_MAC_OS
#else
#include <RkWidgetXWin.h>
#undef KeyPress
#undef KeyRelease
#undef Paint
#endif

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
        widgetImpl->setTitle(title);
}

const std::string& RkWidget::title() const
{
        return widgetImpl->title();
}


void RkWidget::show()
{
        widgetImpl->show();
}

std::shared_ptr<RkNativeWindowInfo> RkWidget::nativeWindowInfo() const
{
        return std::move(widgetImpl->nativeWindowInfo());
}

RkWindowId RkWidget::id() const
{
        return widgetImpl->id();
}

bool RkWidget::isClose() const
{
        return widgetImpl->isClose();
}

void RkWidget::processEvent(const std::shared_ptr<RkEvent> &event)
{
           switch (event->type())
           {
           case RkEvent::Type::Paint:
                   paintEvent(std::dynamic_pointer_cast<RkPaintEvent>(event));
                   break;
           case RkEvent::Type::KeyPress:
                   keyPressEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                   break;
           case RkEvent::Type::KeyRelease:
                   keyReleaseEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                   break;
           case RkEvent::Type::MouseButtonPress:
                   mouseButtonPressEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                   break;
           case RkEvent::Type::MouseButtonRelease:
                   mouseButtonReleaseEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                   break;

           case RkEvent::Type::Resize:
                   resizeEvent(std::dynamic_pointer_cast<RkResizeEvent>(event));
                   break;
	   case RkEvent::Type::Close:
	           closeWidget = true;
                   closeEvent(std::dynamic_pointer_cast<RkCloseEvent>(event));
                   break;
           default:
                   break;
           }
}

void RkWidget::setSize(int x, int y)
{
        widgetImpl->setSize({x, y});
}

void RkWidget::setSize(const std::pair<int, int> &size)
{
        widgetImpl->setSize(size);
}

std::pair<int, int> RkWidget::size() const
{
        return std::move(widgetImpl->size());
}

void RkWidget::setWidth(int w)
{
        widgetImpl->setSize({w, widgetImpl->size().second});
}

int RkWidget::width() const
{
        return widgetImpl->size().first;
}

void RkWidget::setHeight(int h)
{
        widgetImpl->setSize({widgetImpl->size().first, h});
}

int RkWidget::height() const
{
        return widgetImpl->size().second;
}

int RkWidget::x() const
{
        return widgetImpl->x();
}

void RkWidget::setX(int x)
{
        widgetImpl->setX(x);
}

int RkWidget::y() const
{
        return widgetImpl->y();
}

void RkWidget::setY(int y)
{
        return widgetImpl->setY(y);
}

void RkWidget::setBackgroundColor(int r, int g, int b)
{
        widgetImpl->setBackgroundColor(r, g, b);
}

RkWidget* RkWidget::child(const RkWindowId &id) const
{
        return widgetImpl->child(id);
}

void RkWidget::addChild(RkWidget* child)
{
        if (child)
                widgetImpl->addChild(child);
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
