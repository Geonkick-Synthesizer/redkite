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
#ifdef RK_WIN_OS
  : privateWidget(std::make_unique<RkWidgetWin>(parent))
#elif RK_MAC_OS
  : privateWidget(std::make_unique<RkWidgetMac>(parent))
#else
  : privateWidget(parent ? std::make_unique<RkWidgetXWin>(parent->nativeWindowInfo()) : std::make_unique<RkWidgetXWin>())
#endif
  , parentWidget(parent)
  , closeWidget(false)
{
        if (!privateWidget->init()) {
                RK_LOG_ERROR("can't init private widget");
        }

        if (parentWidget)
                parentWidget->addChild(this);
}

RkWidget::RkWidget(const std::shared_ptr<RkNativeWindowInfo> &parent)
#ifdef RK_WIN_OS
  : privateWidget(std::make_unique<RkWidgetWin>(parent))
#elif RK_MAC_OS
  : privateWidget(std::make_unique<RkWidgetMac>(parent))
#else
  : privateWidget(std::make_unique<RkWidgetXWin>(parent))
#endif
{
        if (!privateWidget->init()) {
                RK_LOG_ERROR("can't init private widget");
        }
}

RkWidget::~RkWidget()
{
}

void RkWidget::setTitle(const std::string &title)
{
        privateWidget->setTitle(title);
        widgetTitle = title;
}

const std::string& RkWidget::title() const
{
        return widgetTitle;
}


void RkWidget::show()
{
        privateWidget->show();
}

std::shared_ptr<RkNativeWindowInfo> RkWidget::nativeWindowInfo() const
{
        return std::move(privateWidget->nativeWindowInfo());
}

RkWindowId RkWidget::id() const
{
        return privateWidget->id();
}

bool RkWidget::isClose() const
{
        return closeWidget;
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
        privateWidget->setSize({x, y});
}

void RkWidget::setSize(const std::pair<int, int> &size)
{
        privateWidget->setSize(size);
}

std::pair<int, int> RkWidget::size() const
{
        return std::move(privateWidget->size());
}

void RkWidget::setWidth(int w)
{
        privateWidget->setSize({w, privateWidget->size().second});
}

int RkWidget::width() const
{
        return privateWidget->size().first;
}

void RkWidget::setHeight(int h)
{
        privateWidget->setSize({privateWidget->size().first, h});
}

int RkWidget::height() const
{
        return privateWidget->size().second;
}

int RkWidget::x() const
{
        return privateWidget->x();
}

void RkWidget::setX(int x)
{
        privateWidget->setX(x);
}

int RkWidget::y() const
{
        return privateWidget->y();
}

void RkWidget::setY(int y)
{
        return privateWidget->setY(y);
}

RkWidget* RkWidget::child(const RkWindowId &id) const
{
        return privateWidget->child(id);
}

void RkWidget::addChild(RkWidget* child)
{
        if (child)
                privateWidget->addChild(child);
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
