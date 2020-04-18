/**
 * File name: RkObjectImpl.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor <http://geontime.com>
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

#include "RkObjectImpl.h"
#include "RkEvent.h"
#include "RkPainter.h"

RkObject::RkObjectImpl::RkObjectImpl(RkObject* interface, RkObject* parent)
        : inf_ptr{interface}
        , parentObject{parent}
{
}

RkObject::RkObjectImpl::~RkObjectImpl()
{
        if (evenQueue)
                evenQuque->clearActions(inf_ptr);

        // Remove myself from bound objects.
        for (auto &obj: boundObjects)
                obj->removeObjectObservers(inf_ptr);
        boundObjects.clear();

        // Remove myself from the observers objects.
        for (auto o: observersList) {
                if (o->object())
                        o->object()->removeBoundObject(this);
                delete o;
        }
        rk_observers_list.clear();*/

}


RkObject::RkObjectImpl::RkObjectImpl(RkObject* widgetInterface,
                                     const RkNativeWindowInfo &parent,
                                     Rk::WindowFlags flags)
        : inf_ptr{widgetInterface}
        , parentWidget{nullptr}
#ifdef RK_OS_WIN
        , platformWindow{std::make_unique<RkWindowWin>(parent, flags)}
#elif RK_OS_MAC
        , platformWindow{std::make_unique<RkWindowMac>(parent, flags)}
#else // X11
        , platformWindow{std::make_unique<RkWindowX>(parent, flags)}
#endif
        , widgetClosed{false}
        , eventQueue{nullptr}
        , widgetMinimumSize{0, 0}
        , widgetMaximumSize{1000000, 1000000}
        , widgetSize{platformWindow->size()}
        , widgetAttributes{defaultWidgetAttributes()}
        , widgetModality{(static_cast<int>(flags) & static_cast<int>(Rk::WindowFlags::Dialog)) ? Rk::Modality::ModalTopWindow : Rk::Modality::NonModal}
        , widgetTextColor{0, 0, 0}
        , widgetDrawingColor{0, 0, 0}
        , widgetPointerShape{Rk::PointerShape::Arrow}
        , isGrabKeyEnabled{false}
{
        platformWindow->init();
}

RkObject::RkObjectImpl::~RkObjectImpl()
{
        eventQueue->removeWidget(inf_ptr);

        // Clear object actions.
        eventQueue->clearActions(inf_ptr);

        // Remove all events queued for the
        // current widget from the event queue.
        eventQueue->clearEvents(inf_ptr);

        if (parentWidget)
                parentWidget->removeChild(inf_ptr);

        // Unbind actions
        while (widgetChildren.size() > 0)
                delete widgetChildren.front();
}

Rk::WidgetAttribute RkObject::RkObjectImpl::defaultWidgetAttributes()
{
        return static_cast<Rk::WidgetAttribute>(static_cast<int>(Rk::WidgetAttribute::KeyInputEnabled)
                                                | static_cast<int>(Rk::WidgetAttribute::MouseInputEnabled)
                                                | static_cast<int>(Rk::WidgetAttribute::CloseInputEnabled));

}

void RkObject::RkObjectImpl::show(bool b)
{
	isWidgetSown = b;
        platformWindow->show(isWidgetSown);
}

bool RkObject::RkObjectImpl::isShown() const
{
	return isWidgetSown;
}

void RkObject::RkObjectImpl::setTitle(const std::string &title)
{
        widgetTitle = title;
        platformWindow->setTitle(widgetTitle);
}

const std::string& RkObject::RkObjectImpl::title() const
{
        return widgetTitle;
}

std::shared_ptr<RkNativeWindowInfo> RkObject::RkObjectImpl::nativeWindowInfo() const
{
        return platformWindow->nativeWindowInfo();
}

bool RkObject::RkObjectImpl::isClose() const
{
        return widgetClosed;
}

RkWindowId RkObject::RkObjectImpl::id() const
{
        return platformWindow->id();
}

void RkObject::RkObjectImpl::processEvent(const std::shared_ptr<RkEvent> &event)
{
        switch (event->type())
        {
        case RkEvent::Type::Paint:
        {
                inf_ptr->paintEvent(std::dynamic_pointer_cast<RkPaintEvent>(event));
                break;
        }
        case RkEvent::Type::KeyPressed:
        {
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Rk::WidgetAttribute::KeyInputEnabled))
                        inf_ptr->keyPressEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                auto topWidget = inf_ptr->getTopWindow();
                if ( topWidget != nullptr
                    && propagateGrabKeyEnabled()
                    && topWidget->grabKeyEnabled()
                    && topWidget->isInputEnabled()) {
                        topWidget->keyPressEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                }
                break;
        }
        case RkEvent::Type::KeyReleased:
        {
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Rk::WidgetAttribute::KeyInputEnabled))
                        inf_ptr->keyReleaseEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                auto topWidget = inf_ptr->getTopWindow();
                if ( topWidget != nullptr
                    && propagateGrabKeyEnabled()
                    && topWidget->grabKeyEnabled()
                    && topWidget->isInputEnabled()) {
                        topWidget->keyReleaseEvent(std::dynamic_pointer_cast<RkKeyEvent>(event));
                }
                break;
        }
        case RkEvent::Type::FocusedIn:
                inf_ptr->focusEvent(std::dynamic_pointer_cast<RkFocusEvent>(event));
                break;
        case RkEvent::Type::FocusedOut:
                inf_ptr->focusEvent(std::dynamic_pointer_cast<RkFocusEvent>(event));
                break;
        case RkEvent::Type::MouseButtonPress:
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Rk::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->mouseButtonPressEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::MouseDoubleClick:
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Rk::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->mouseDoubleClickEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::MouseButtonRelease:
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Rk::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->mouseButtonReleaseEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::MouseMove:
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Rk::WidgetAttribute::MouseInputEnabled))
                        inf_ptr->mouseMoveEvent(std::dynamic_pointer_cast<RkMouseEvent>(event));
                break;
        case RkEvent::Type::Resize:
                widgetSize = platformWindow->size();
                platformWindow->resizeCanvas();
                inf_ptr->resizeEvent(std::dynamic_pointer_cast<RkResizeEvent>(event));
                break;
	case RkEvent::Type::Show:
		isWidgetSown = true;
                inf_ptr->showEvent(std::dynamic_pointer_cast<RkShowEvent>(event));
                break;
	case RkEvent::Type::Hide:
		isWidgetSown = false;
                inf_ptr->hideEvent(std::dynamic_pointer_cast<RkHideEvent>(event));
                break;
        case RkEvent::Type::DeleteChild:
                deleteChild(std::dynamic_pointer_cast<RkDeleteChild>(event)->child());
                break;
        case RkEvent::Type::Close:
                if (static_cast<int>(widgetAttributes) & static_cast<int>(Rk::WidgetAttribute::CloseInputEnabled)) {
                        widgetClosed = true;
                        inf_ptr->closeEvent(std::dynamic_pointer_cast<RkCloseEvent>(event));
                }
                break;
        default:
                break;
        }
}

RkObject* RkObject::RkObjectImpl::parent() const
{
        return parentWidget;
}

RkObject* RkObject::RkObjectImpl::child(const RkWindowId &id) const
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

void RkObject::RkObjectImpl::addChild(RkObject* child)
{
        objectChildren.insert(child);
        if (eventQueue)
                eventQueue->addObject(child);
}

void RkObject::RkObjectImpl::removeChild(RkObject* child)
{
        for (auto it = widgetChildren.begin(); it != widgetChildren.end(); ++it) {
                if (*it == child) {
                        widgetChildren.erase(it);
                        return;
                }
        }
}

void RkObject::RkObjectImpl::setSize(const RkSize &size)
{
        if (size.width() > 1 && size.height() > 1)
                platformWindow->setSize(size);
        widgetSize = size;
}

RkSize RkObject::RkObjectImpl::size() const
{
        return  widgetSize;
}

int RkObject::RkObjectImpl::minimumWidth() const
{
        return widgetMinimumSize.width();
}

int RkObject::RkObjectImpl::maximumWidth() const
{
        return widgetMaximumSize.width();
}

int RkObject::RkObjectImpl::minimumHeight() const
{
        return widgetMinimumSize.height();
}

int RkObject::RkObjectImpl::maximumHeight() const
{
        return widgetMaximumSize.height();
}

void RkObject::RkObjectImpl::setMinimumWidth(int width)
{
        widgetMinimumSize.setWidth(width);
}

void RkObject::RkObjectImpl::setMaximumWidth(int width)
{
        widgetMaximumSize.setWidth(width);
}

void RkObject::RkObjectImpl::setMinimumHeight(int height)
{
        widgetMinimumSize.setHeight(height);
}

void RkObject::RkObjectImpl::setMaximumHeight(int height)
{
        widgetMaximumSize.setHeight(height);
}

void RkObject::RkObjectImpl::setPosition(const RkPoint &position)
{
        platformWindow->setPosition(position);
}

RkPoint RkObject::RkObjectImpl::position() const
{
        return platformWindow->position();
}

void RkObject::RkObjectImpl::setBorderWidth(int width)
{
        platformWindow->setBorderWidth(width);
}

int RkObject::RkObjectImpl::borderWidth() const
{
        return platformWindow->borderWidth();
}

void RkObject::RkObjectImpl::setBorderColor(const RkColor &color)
{
        platformWindow->setBorderColor(color);
}

const RkColor& RkObject::RkObjectImpl::borderColor() const
{
        return platformWindow->borderColor();
}

void RkObject::RkObjectImpl::setBackgroundColor(const RkColor &color)
{
        platformWindow->setBackgroundColor(color);
        widgetBackground = color;
}

const RkColor& RkObject::RkObjectImpl::background() const
{
        return widgetBackground;
}

RkRect RkObject::RkObjectImpl::rect() const
{
        return RkRect(RkPoint(0, 0), size());
}

void RkObject::RkObjectImpl::setEventQueue(RkEventQueue *queue)
{
        if (!eventQueue) {
                eventQueue = queue;
                platformWindow->setEventQueue(eventQueue);
                for (const auto &child : widgetChildren)
                        eventQueue->addWidget(child);
        }
}

RkEventQueue* RkObject::RkObjectImpl::getEventQueue()
{
        return eventQueue;
}

std::shared_ptr<RkCanvasInfo> RkObject::RkObjectImpl::getCanvasInfo() const
{
        return platformWindow->getCanvasInfo();
}

void RkObject::RkObjectImpl::update()
{
        platformWindow->update();
}

void RkObject::RkObjectImpl::deleteChild(RkObject* child)
{
        for (auto it = widgetChildren.begin(); it != widgetChildren.end(); ++it) {
                if (*it == child) {
                        it = widgetChildren.erase(it);
                        delete child;
                        return;
                }
        }
}

Rk::Modality RkObject::RkObjectImpl::modality() const
{
        return widgetModality;
}

const std::list<RkObject*>& RkObject::RkObjectImpl::childWidgets() const
{
        return widgetChildren;
}

void RkObject::RkObjectImpl::setWidgetAttribute(Rk::WidgetAttribute attribute)
{
        widgetAttributes = static_cast<Rk::WidgetAttribute>(static_cast<int>(widgetAttributes) | static_cast<int>(attribute));
}

void RkObject::RkObjectImpl::clearWidgetAttribute(Rk::WidgetAttribute attribute)
{
        widgetAttributes = static_cast<Rk::WidgetAttribute>(static_cast<int>(widgetAttributes) & (~static_cast<int>(attribute)));
}

Rk::WidgetAttribute RkObject::RkObjectImpl::getWidgetAttributes() const
{
        return widgetAttributes;
}

void RkObject::RkObjectImpl::setFocus(bool b)
{
        platformWindow->setFocus(b);
}

bool RkObject::RkObjectImpl::hasFocus() const
{
        return platformWindow->hasFocus();
}

void RkObject::RkObjectImpl::setTextColor(const RkColor &color)
{
        widgetTextColor = color;
}

const RkColor& RkObject::RkObjectImpl::textColor() const
{
        return widgetTextColor;
}

const RkColor& RkObject::RkObjectImpl::color() const
{
        return widgetDrawingColor;
}

void RkObject::RkObjectImpl::setColor(const RkColor &color)
{
        widgetDrawingColor = color;
}

const RkFont& RkObject::RkObjectImpl::font() const
{
        return widgetFont;
}

void RkObject::RkObjectImpl::setFont(const RkFont &font)
{
        widgetFont = font;
}

void RkObject::RkObjectImpl::setPointerShape(Rk::PointerShape shape)
{
        if (widgetPointerShape != shape) {
                widgetPointerShape = shape;
                platformWindow->setPointerShape(widgetPointerShape);
        }
}

Rk::PointerShape RkObject::RkObjectImpl::pointerShape() const
{
        return widgetPointerShape;
}

void RkObject::RkObjectImpl::enableGrabKey(bool b)
{
        isGrabKeyEnabled = b;
}

bool RkObject::RkObjectImpl::grabKeyEnabled() const
{
        return isGrabKeyEnabled;
}

void RkObject::RkObjectImpl::propagateGrabKey(bool b)
{
        isPropagateGrabKey = b;
}

bool RkObject::RkObjectImpl::propagateGrabKeyEnabled() const
{
        return isPropagateGrabKey;
}


void RkObject::rk_add_observer(RkObserver *observer)
{
        rk_observers_list.push_back(observer);
}

void RkObject::rk_remove_object_observers(RkObject *obj)
{
        rk_observers_list.erase(std::remove_if(rk_observers_list.begin(),
                                               rk_observers_list.end(),
                                               [obj](RkObserver *o)  {
                                                       if (o->object() == nullptr) {
                                                               return false;
                                                       } else if(o->object() == obj) {
                                                               delete o;
                                                               return true;
                                                       }
                                                       return false;
                                               })
                                , rk_observers_list.end());
}

std::vector<RkObserver*>& RkObject::rk_get_observers()
{
        return rk_observers_list;
}

void RkObject::rk_add_bound_object(RkObject *obj)
{
        auto res = std::find(std::begin(rk_bound_objects), std::end(rk_bound_objects), obj);
        if (res == std::end(rk_bound_objects))
                rk_bound_objects.push_back(obj);
}

void RkObject::rk_remove_bound_object(RkObject *obj)
{
        rk_bound_objects.erase(std::remove_if(rk_bound_objects.begin(),
                                              rk_bound_objects.end(),
                                              [obj](RkObject *o)  {
                                                      if (o == obj)
                                                              return true;
                                                      return false;
                                              })
                               , rk_bound_objects.end());
}
