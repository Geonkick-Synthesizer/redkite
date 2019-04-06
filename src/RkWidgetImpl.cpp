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
#include "RkPainter.h"

#ifdef RK_OS_WIN
#include "RkWindowWin.h"
#elif RK_OS_MAC
#include "RkWindowMac.h"
#else // X11
#include "RkWindowX.h"
#undef KeyPress
#undef KeyRelease
#undef Paint
#endif

RkWidget::RkWidgetImpl::RkWidgetImpl(RkWidget* widgetInterface, RkWidget* parent)
        : inf_ptr{widgetInterface}
        , parentWidget{parent}
#ifdef RK_OS_WIN
        , platformWindow{!parent ? std::make_unique<RkWindowWin>() : std::make_unique<RkWindowWin>(parent->nativeWindowInfo())}
#elif RK_OS_MAC
        , platformWindow{!parent ? std::make_unique<RkWindowMac>() : std::make_unique<RkWindowMac>(parent->nativeWindowInfo())}
#else // X11
        , platformWindow{!parent ? std::make_unique<RkWindowX>() : std::make_unique<RkWindowX>(parent->nativeWindowInfo())}
#endif
        , widgetClosed{false}
        , eventQueue{nullptr}
        , widgetMinimumSize{0, 0}
        , widgetMaximumSize{1000000, 1000000}
{
        platformWindow->init();
}

RkWidget::RkWidgetImpl::RkWidgetImpl(RkWidget* widgetInterface, const RkNativeWindowInfo &parent)
        : inf_ptr{widgetInterface}
        , parentWidget{nullptr}
#ifdef RK_OS_WIN
        , platformWindow{std::make_unique<RkWindowWin>(parent)}
#elif RK_OS_MAC
        , platformWindow{std::make_unique<RkWindowMac>(parent)}
#else // X11
        , platformWindow{std::make_unique<RkWindowX>(parent)}
#endif
        , widgetClosed{false}
        , eventQueue{nullptr}
        , widgetMinimumSize{0, 0}
        , widgetMaximumSize{1000000, 1000000}
{
        platformWindow->init();
}

RkWidget::RkWidgetImpl::~RkWidgetImpl()
{
        for (auto child : widgetChildren)
                delete child;
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
        {
                inf_ptr->paintEvent(std::dynamic_pointer_cast<RkPaintEvent>(event));
                break;
        }
        case RkEvent::Type::KeyPressed:
                inf_ptr->keyPressEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                break;
        case RkEvent::Type::KeyReleased:
                inf_ptr->keyReleaseEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                break;
        case RkEvent::Type::MouseButtonPress:
                inf_ptr->mouseButtonPressEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::MouseDoubleClick:
                inf_ptr->mouseDoubleClickEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::MouseButtonRelease:
                break;
        case RkEvent::Type::Resize:
                inf_ptr->resizeEvent(std::dynamic_pointer_cast<RkResizeEvent>(event));
                platformWindow->resizeCanvas();
                break;
        case RkEvent::Type::Close:
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
                if (eventQueue)
                        eventQueue->addWidget(child);
        }
}

void RkWidget::RkWidgetImpl::setSize(const RkSize &size)
{
        if (size.width() > 1 && size.height() > 1)
                platformWindow->setSize(size);
}

RkSize RkWidget::RkWidgetImpl::size() const
{
        return  platformWindow->size();
}

int RkWidget::RkWidgetImpl::minimumWidth() const
{
        return widgetMinimumSize.width();
}

int RkWidget::RkWidgetImpl::maximumWidth() const
{
        return widgetMaximumSize.width();
}

int RkWidget::RkWidgetImpl::minimumHeight() const
{
        return widgetMinimumSize.height();
}

int RkWidget::RkWidgetImpl::maximumHeight() const
{
        return widgetMaximumSize.height();
}

void RkWidget::RkWidgetImpl::setMinimumWidth(int width)
{
        widgetMinimumSize.setWidth(width);
}

void RkWidget::RkWidgetImpl::setMaximumWidth(int width)
{
        widgetMaximumSize.setWidth(width);
}

void RkWidget::RkWidgetImpl::setMinimumHeight(int height)
{
        widgetMinimumSize.setHeight(height);
}

void RkWidget::RkWidgetImpl::setMaximumHeight(int height)
{
        widgetMaximumSize.setHeight(height);
}

void RkWidget::RkWidgetImpl::setPosition(const RkPoint &position)
{
        platformWindow->setPosition(position);
}

RkPoint RkWidget::RkWidgetImpl::position() const
{
        return platformWindow->position();
}

void RkWidget::RkWidgetImpl::setBorderWidth(int width)
{
        platformWindow->setBorderWidth(width);
}

int RkWidget::RkWidgetImpl::borderWidth() const
{
        return platformWindow->borderWidth();
}

void RkWidget::RkWidgetImpl::setBorderColor(const RkColor &color)
{
        platformWindow->setBorderColor(color);
}

const RkColor& RkWidget::RkWidgetImpl::borderColor() const
{
        return platformWindow->borderColor();
}

void RkWidget::RkWidgetImpl::setBackgroundColor(const RkColor &color)
{
        platformWindow->setBackgroundColor(color);
}

const RkColor& RkWidget::RkWidgetImpl::background() const
{
        return platformWindow->background();
}

RkRect RkWidget::RkWidgetImpl::rect() const
{
        return RkRect(RkPoint(0, 0), size());
}

void RkWidget::RkWidgetImpl::setEventQueue(RkEventQueue *queue)
{
        if (!eventQueue) {
                eventQueue = queue;
                platformWindow->setEventQueue(eventQueue);
                for (const auto &child : widgetChildren)
                        eventQueue->addWidget(child);
        }
}

RkEventQueue* RkWidget::RkWidgetImpl::getEventQueue()
{
        return eventQueue;
}

std::shared_ptr<RkCanvasInfo> RkWidget::RkWidgetImpl::getCanvasInfo() const
{
        return platformWindow->getCanvasInfo();
}

void RkWidget::RkWidgetImpl::update()
{
        platformWindow->update();
}
