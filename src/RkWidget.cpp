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

#ifdef RK_WIN_OS
#include "RkWidgetWin.h"
#elif RK_MAC_OS
#include "RkWidgetMac.h"
#else
#include "RkWidgetXWin.h"
#endif

RkWidget::RkWidget(RkWidget *parent)
#ifdef RK_WIN_OS
  : privateWidget(std::make_unique<RkWidgetWin>(parent))
#elif RK_MAC_OS
  : privateWidget(std::make_unique<RkWidgetMac>(parent))
#else
    : privateWidget(parent ? std::make_unique<RkWidgetXWin>(parent->nativeWindow()) : std::make_unique<RkWidgetXWin>())
#endif
{
        if (!privateWidget->init()) {
                RK_LOG_ERROR("can't init private widget");
        }
}

RkWidget::RkWidget(RkNativeWindow parent)
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

RkWidget::RkNativeWindow RkWidget::nativeWindow()
{
        return privateWidget->getWindow();
}

void RkWidget::pocessEvents()
{
        std::list<std::shared_ptr<RkEvent>> events = privateWidget->getEvents();
        for (auto &event: events) {
           switch (event->type())
           {
           case RkEvent::Type::Paint:
                   paintEvent(std::dynamic_pointer_cast<RkPaintEvent>(event));
                   break;
           case RkEvent::Type::KeyPressEvent:
                   keyPressEvent(std::dynamic_pointer_cast<RkKeyPressEvent>(event));
                   break;
           case RkEvent::Type::KeyReleaseEvent:
                   keyReleaseEvent(std::dynamic_pointer_cast<RkKeyReleaseEvent>(event));
                   break;
           default:
                   break;
           }
        }
        processChildEvents();
}

void RkWidget::processChildEvents()
{
        // TODO: implement.
}

void RkWidget::closeEvent(std::shared_ptr<RkCloseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::keyPressEvent(std::shared_ptr<RkKeyEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::keyReleaseEvent(std::shared_ptr<RkKeyEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::paintEvent(std::shared_ptr<RkPainEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::mousePressEvent(std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::mouseReleaseEvent(std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::mouseDoubleClickEvent(std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::mouseMoveEvent(std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::paintEvent(std::shared_ptr<RkPainEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::wheelEvent(std::shared_ptr<RkPainEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::resizeEvent(std::shared_ptr<RkResizeEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::showEvent(std::shared_ptr<RkShowEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::hideEvent(std::shared_ptr<RkHideEvent> &event)
{
        RK_UNUSED(event);
}
