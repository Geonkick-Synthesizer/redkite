/**
 * File name: RkWidgetImpl.cpp
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

#include "RkWidgetImpl.h"
#include "RkEvent.h"

#ifdef RK_OS_WIN
#include "RkWindowWin.h"
#elif RK_OS_MAC
#else
#include "RkWindowX.h"
#undef KeyPress
#undef KeyRelease
#undef Paint
#endif

RkWidget::RkWidgetImpl::RkWidgetImpl(RkWidget* widgetInterface, RkWidget* parent)
        : inf_ptr{widgetInterface}
        , parentWidget{parent}
        , platformWindow{!parent ? std::make_unique<RkWindowWin>() : std::make_unique<RkWindowWin>(parent->nativeWindowInfo())}
        , widgetClosed{false}
        , eventQueue{nullptr}
{
        platformWindow->init();
}

RkWidget::RkWidgetImpl::RkWidgetImpl(RkWidget* widgetInterface, const RkNativeWindowInfo &parent)
        : inf_ptr{widgetInterface}
        , parentWidget{nullptr}
        , platformWindow{std::make_unique<RkWindowWin>(parent)}
        , widgetClosed{false}
        , eventQueue{nullptr}
{
        platformWindow->init();
}

RkWidget::RkWidgetImpl::~RkWidgetImpl()
{
        RK_LOG_DEBUG("delete children " << widgetChildren.size());
        for (auto child : widgetChildren) {
                RK_LOG_DEBUG("delete child " << child->title());
                delete child;
        }
}

void RkWidget::RkWidgetImpl::show()
{
        platformWindow->show();
}

void RkWidget::RkWidgetImpl::setTitle(const std::string &title)
{
        widgetTitle = title;
        platformWindow->setTitle(widgetTitle);
}

const std::string& RkWidget::RkWidgetImpl::title() const
{
        return widgetTitle;
}

std::shared_ptr<RkNativeWindowInfo> RkWidget::RkWidgetImpl::nativeWindowInfo() const
{
        return platformWindow->nativeWindowInfo();
}

bool RkWidget::RkWidgetImpl::isClose() const
{
        return widgetClosed;
}

RkWindowId RkWidget::RkWidgetImpl::id() const
{
        return platformWindow->id();
}

void RkWidget::RkWidgetImpl::processEvent(const std::shared_ptr<RkEvent> &event)
{
        switch (event->type())
        {
        case RkEvent::Type::Paint:
                inf_ptr->paintEvent(std::dynamic_pointer_cast<RkPaintEvent>(event));
                break;
        case RkEvent::Type::KeyPress:
		        OutputDebugString("[REDKITE]Event:RkEvent::Type::KeyPress");
                inf_ptr->keyPressEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                break;
        case RkEvent::Type::KeyRelease:
		        OutputDebugString("[REDKITE]RkEvent::Type::KeyPress");
                inf_ptr->keyReleaseEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                break;
        case RkEvent::Type::MouseButtonPress:
		        OutputDebugString("[REDKITE]RkEvent::Type::Button");
                inf_ptr->mouseButtonPressEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::MouseButtonRelease:
                inf_ptr->mouseButtonReleaseEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::Resize:
                inf_ptr->resizeEvent(std::dynamic_pointer_cast<RkResizeEvent>(event));
                break;
        case RkEvent::Type::Close:
		        OutputDebugString("[REDKITE]RkEvent::Type::Close");
                widgetClosed = true;
                inf_ptr->closeEvent(std::dynamic_pointer_cast<RkCloseEvent>(event));
                break;
        default:
                break;
        }
}

RkWidget* RkWidget::RkWidgetImpl::parent() const
{
        return parentWidget;
}

RkWidget* RkWidget::RkWidgetImpl::child(const RkWindowId &id) const
{
        for (const auto &child : widgetChildren) {
                if (child->id().id == id.id) {
                        return child;
                } else {
                        auto ch = child->child(id);
                        if (ch)
                                return ch;
                }
        }

        return nullptr;
}

void RkWidget::RkWidgetImpl::addChild(RkWidget* child)
{
        if (child) {
                widgetChildren.push_back(child);
                eventQueue->addWidget(child);
        }
}

void RkWidget::RkWidgetImpl::setSize(const std::pair<int, int> &size)
{
        if (size.first > 1 && size.second > 1)
                platformWindow->setSize(size);
}

std::pair<int, int> RkWidget::RkWidgetImpl::size() const
{
        return  platformWindow->size();
}

void RkWidget::RkWidgetImpl::setPosition(const std::pair<int, int> &position)
{
        platformWindow->setPosition(position);
}

std::pair<int, int> RkWidget::RkWidgetImpl::position() const
{
        return platformWindow->position();
}

void RkWidget::RkWidgetImpl::setBorderWidth(int width)
{
        platformWindow->setBorderWidth(width);
}

void RkWidget::RkWidgetImpl::setBorderColor(const std::tuple<int, int, int> &color)
{
        platformWindow->setBorderColor(color);
}

void RkWidget::RkWidgetImpl::setBackgroundColor(const std::tuple<int, int, int> &background)
{
        platformWindow->setBackgroundColor(background);
}

void RkWidget::RkWidgetImpl::setEventQueue(const std::shared_ptr<RkEventQueue> &queue)
{
        eventQueue = queue;
        platformWindow->setEventQueue(eventQueue);
}

std::shared_ptr<RkEventQueue> RkWidget::RkWidgetImpl::getEventQueue()
{
        return eventQueue;
}
