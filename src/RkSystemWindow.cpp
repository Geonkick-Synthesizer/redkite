/**
 * File name: RkSystemWindow.cpp
 * Project: Redkite (A lightweight graphics widget toolkit for embedded GUI)
 *
 * Copyright (C) 2023 Iurie Nistor
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
#include "RkSystemWindow.h"
#include "RkEvent.h"
#include "RkSystemWindowImpl.h"
#include "RkPlatform.h"
#include "RkMain.h"

#ifdef RK_OS_WIN
#include "RkWindowWin.h"
#elif RK_OS_MAC
#include "RkWindowMac.h"
#else // X11
#include "RkWindowX.h"
#undef KeyPress
#undef KeyRelease
#undef Paint
#undef FocusIn
#undef FocusOut
#endif

RkSystemWindow::RkSystemWindow(RkWidgetImpl *widget, const RkNativeWindowInfo* parent)
        : topWidget{widget}
#ifdef RK_OS_WIN
        platformWindow{std::make_unique<RkWindowWin>(parent)}
#else // X11
        platformWindow{std::make_unique<RkWindowX>(parent)}
#endif // X11
        , windowSize{platformWindow->size()}
        , windowBackground{platformWindow->background()}
        , windowAttributes{defaultWindowAttributes()}
        , windowTextColor{0, 0, 0}
        , windowDrawingColor{0, 0, 0}
        , windowPointerShape{Rk::PointerShape::Arrow}
        , isGrabKeyEnabled{false}
        , isPropagateGrabKey{true}
{
        topWidget->setSystemWindow(this);
}

RkSystemWindow::~RkSystemWindow()
{
}

void RkSystemWindow::setTitle(const std::string &title)
{
        platformWindow->setTitle(windowTitle);
}

const std::string& RkSystemWindow::title() const
{
        return windowTitle;
}


void RkSystemWindow::show(bool b)
{
        impl_ptr->show(b);
}

bool RkSystemWindow::isShown() const
{
	return impl_ptr->isShown();
}

void RkSystemWindow::hide()
{
        impl_ptr->show(false);
}

const RkNativeWindowInfo* RkSystemWindow::nativeWindowInfo() const
{
        return impl_ptr->nativeWindowInfo();
}

RkWindowId RkSystemWindow::id() const
{
        return impl_ptr->id();
}

RkSystemWindow* RkSystemWindow::parentWidget() const
{
        return dynamic_cast<RkSystemWindow*>(parent());
}

bool RkSystemWindow::isClose() const
{
        return impl_ptr->isClose();
}

void RkSystemWindow::setSize(int w, int h)
{
        if (w > maximumWidth())
                w = maximumWidth();
        else if (w < minimumWidth())
                w = minimumWidth();

        if (h > maximumHeight())
                h = maximumHeight();
        else if (h < minimumHeight())
                h = minimumHeight();

        impl_ptr->setSize(RkSize(w, h));
}

void RkSystemWindow::setSize(const RkSize &size)
{
        impl_ptr->setSize(size);
}

RkSize RkSystemWindow::size() const
{
        return impl_ptr->size();
}

void RkSystemWindow::setWidth(int w)
{
        if (w > maximumWidth())
                impl_ptr->setSize(RkSize(maximumWidth(), impl_ptr->size().height()));
        else if (w < minimumWidth())
                impl_ptr->setSize(RkSize(minimumWidth(), impl_ptr->size().height()));
        else
                impl_ptr->setSize(RkSize(w, impl_ptr->size().height()));
}

int RkSystemWindow::width() const
{
        return impl_ptr->size().width();
}

int RkSystemWindow::minimumWidth() const
{
        return impl_ptr->minimumWidth();
}

int RkSystemWindow::maximumWidth() const
{
        return impl_ptr->maximumWidth();
}

void RkSystemWindow::setHeight(int h)
{
        if (h > maximumHeight())
                impl_ptr->setSize(RkSize(impl_ptr->size().width(),  maximumHeight()));
        else if (h < minimumHeight())
                impl_ptr->setSize(RkSize(impl_ptr->size().width(),  minimumHeight()));
        else
                impl_ptr->setSize(RkSize(impl_ptr->size().width(),  h));
}

int RkSystemWindow::height() const
{
        return impl_ptr->size().height();
}

int RkSystemWindow::minimumHeight() const
{
        return impl_ptr->minimumHeight();
}

int RkSystemWindow::maximumHeight() const
{
        return impl_ptr->maximumHeight();
}

void RkSystemWindow::setMinimumWidth(int width)
{
        impl_ptr->setMinimumWidth(width);
}

void RkSystemWindow::setMinimumHeight(int height)
{
        impl_ptr->setMinimumHeight(height);
}

void RkSystemWindow::setMaximumWidth(int width)
{
        impl_ptr->setMaximumWidth(width);
}

void RkSystemWindow::setMaximumHeight(int height)
{
        impl_ptr->setMaximumHeight(height);
}

void RkSystemWindow::setFixedWidth(int width)
{
        setMinimumWidth(width);
        setMaximumWidth(width);
        setWidth(width);
}

void RkSystemWindow::setFixedHeight(int height)
{
        setMinimumHeight(height);
        setMaximumHeight(height);
        setHeight(height);
}

void RkSystemWindow::setFixedSize(const RkSize &size)
{
        setMinimumWidth(size.width());
        setMaximumWidth(size.width());
        setMinimumHeight(size.height());
        setMaximumHeight(size.height());
        setSize(size);
}

void RkSystemWindow::setFixedSize(int width, int height)
{
        setFixedSize(RkSize(width, height));
}

int RkSystemWindow::x() const
{
        return impl_ptr->position().x();
}

void RkSystemWindow::setX(int x)
{
        impl_ptr->setPosition(RkPoint(x, impl_ptr->position().y()));
}

int RkSystemWindow::y() const
{
        return impl_ptr->position().y();
}

void RkSystemWindow::setY(int y)
{
        return impl_ptr->setPosition(RkPoint(impl_ptr->position().x(), y));
}

void RkSystemWindow::setPosition(int x, int y)
{
        impl_ptr->setPosition(RkPoint(x, y));
}

void RkSystemWindow::setPosition(const RkPoint &p)
{
        impl_ptr->setPosition(p);
}

RkPoint RkSystemWindow::position() const
{
        return impl_ptr->position();
}

void RkSystemWindow::setBorderWidth(int width)
{
        impl_ptr->setBorderWidth(width);
}

int RkSystemWindow::borderWidth() const
{
        return impl_ptr->borderWidth();
}

void RkSystemWindow::setBorderColor(int red, int green, int blue)
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
        impl_ptr->setBorderColor(RkColor(red, green, blue));
}

const RkColor& RkSystemWindow::borderColor() const
{
        return impl_ptr->borderColor();
}

void RkSystemWindow::setBackgroundColor(int red, int green, int blue)
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

        impl_ptr->setBackgroundColor(RkColor(red, green, blue));
}

void RkSystemWindow::setBackgroundColor(const RkColor &color)
{
        impl_ptr->setBackgroundColor(color);
}

const RkColor& RkSystemWindow::background() const
{
        return impl_ptr->background();
}

void RkSystemWindow::setTextColor(const RkColor &color)
{
        return impl_ptr->setTextColor(color);
}

const RkColor& RkSystemWindow::textColor() const
{
        return impl_ptr->textColor();
}

const RkColor& RkSystemWindow::color() const
{
        return impl_ptr->color();
}

void RkSystemWindow::setColor(const RkColor &color)
{
        return impl_ptr->setColor(color);
}

const RkFont& RkSystemWindow::font() const
{
        return impl_ptr->font();
}

void RkSystemWindow::setFont(const RkFont &font)
{
        impl_ptr->setFont(font);
}

void RkSystemWindow::enableInput()
{
        setWidgetAttribute(static_cast<Rk::WidgetAttribute>(static_cast<int>(Rk::WidgetAttribute::KeyInputEnabled)
                           | static_cast<int>(Rk::WidgetAttribute::MouseInputEnabled)
                           | static_cast<int>(Rk::WidgetAttribute::CloseInputEnabled)));
        for (const auto &ch: children()) {
                auto widget = dynamic_cast<RkSystemWindow*>(ch);
                if (widget)
                        widget->enableInput();
        }
}

void RkSystemWindow::disableInput()
{
        if (modality() == Rk::Modality::ModalParent || modality() == Rk::Modality::ModalTopWidget)
                return;

        clearWidgetAttribute(static_cast<Rk::WidgetAttribute>(static_cast<int>(Rk::WidgetAttribute::KeyInputEnabled)
                            | static_cast<int>(Rk::WidgetAttribute::MouseInputEnabled)
                            | static_cast<int>(Rk::WidgetAttribute::CloseInputEnabled)));
        for (const auto &ch: children()) {
                auto widget = dynamic_cast<RkSystemWindow*>(ch);
                if (widget)
                        widget->disableInput();
        }
}

bool RkSystemWindow::isInputEnabled() const
{
        return  static_cast<int>(widgetAttributes()) & static_cast<int>(Rk::WidgetAttribute::KeyInputEnabled);
}

void RkSystemWindow::enableGrabKey(bool b)
{
        // For now only for top level window.
        if (!parentWidget())
                impl_ptr->enableGrabKey(b);
}

bool RkSystemWindow::grabKeyEnabled() const
{
        return impl_ptr->grabKeyEnabled();
}

void RkSystemWindow::propagateGrabKey(bool b)
{
        impl_ptr->propagateGrabKey(b);
}

bool RkSystemWindow::propagateGrabKeyEnabled() const
{
        return impl_ptr->propagateGrabKeyEnabled();
}

void RkSystemWindow::event(RkEvent *event)
{
        impl_ptr->event(event);
        RkObject::event(event);
}

void RkSystemWindow::closeEvent([[maybe_unused]] RkCloseEvent *event)
{
        if (parentWidget()) {
                auto event = std::make_unique<RkDeleteChild>(parentWidget(), this);
                eventQueue()->postEvent(parentWidget(), std::move(event));
        }
}

void RkSystemWindow::keyPressEvent(RkKeyEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::keyReleaseEvent(RkKeyEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::shortcutEvent(RkKeyEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::mouseMoveEvent(RkMouseEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::mouseButtonPressEvent(RkMouseEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::mouseButtonReleaseEvent(RkMouseEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::mouseDoubleClickEvent(RkMouseEvent *event)
{
        mouseButtonPressEvent(event);
}

void RkSystemWindow::wheelEvent(RkWheelEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::dropEvent(RkDropEvent *event)
{
        if (parentWidget())
                getTopWidget()->dropEvent(event);
}

void RkSystemWindow::moveEvent(RkMoveEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::resizeEvent(RkResizeEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::paintEvent(RkPaintEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::showEvent(RkShowEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::hideEvent(RkHideEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::focusEvent([[maybe_unused]] RkFocusEvent *event)
{
        update();
}

void RkSystemWindow::hoverEvent(RkHoverEvent *event)
{
        RK_UNUSED(event);
}

void RkSystemWindow::update()
{
        impl_ptr->update();
}

const RkCanvasInfo* RkSystemWindow::getCanvasInfo() const
{
        return impl_ptr->getCanvasInfo();
}

void RkSystemWindow::freeCanvasInfo()
{
        return impl_ptr->freeCanvasInfo();
}

RkRect RkSystemWindow::rect() const
{
        return impl_ptr->rect();
}

void RkSystemWindow::close()
{
        eventQueue()->postEvent(this, std::make_unique<RkCloseEvent>());
}

bool RkSystemWindow::isModal() const
{
        return modality() != Rk::Modality::NonModal;
}

Rk::Modality RkSystemWindow::modality() const
{
        return impl_ptr->modality();
}

void RkSystemWindow::setWidgetAttribute(Rk::WidgetAttribute attribute)
{
        impl_ptr->setWidgetAttribute(attribute);
}

void RkSystemWindow::clearWidgetAttribute(Rk::WidgetAttribute attribute)
{
        impl_ptr->clearWidgetAttribute(attribute);
}

Rk::WidgetAttribute RkSystemWindow::widgetAttributes() const
{
        return impl_ptr->getWidgetAttributes();
}

RkSystemWindow* RkSystemWindow::getTopWidget()
{
        if (!parentWidget())
                return this;
        return parentWidget()->getTopWidget();
}

bool RkSystemWindow::isTopWindow() const
{
        return !parentWidget();
}

void RkSystemWindow::setFocus(bool b)
{
        impl_ptr->setFocus(b);
}

bool RkSystemWindow::hasFocus() const
{
        return impl_ptr->hasFocus();
}

void RkSystemWindow::setPointerShape(Rk::PointerShape shape)
{
        impl_ptr->setPointerShape(shape);
}

Rk::PointerShape RkSystemWindow::pointerShape() const
{
        return impl_ptr->pointerShape();
}

void RkSystemWindow::setScaleFactor(double factor)
{
        impl_ptr->setScaleFactor(factor);
        for (const auto &ch: children()) {
                auto widget = dynamic_cast<RkSystemWindow*>(ch);
                if (widget)
                        widget->setScaleFactor(factor);
        }

        if (this == getTopWidget())
            eventQueue()->setScaleFactor(factor);
        update();
}

double RkSystemWindow::scaleFactor() const
{
        return impl_ptr->scaleFactor();
}


bool RkSystemWindow::pointerIsOverWindow() const
{
        return impl_ptr->pointerIsOverWindow();
}

bool RkSystemWindow::isChild(RkSystemWindow *widget)
{
        for (const auto &child: children()) {
                if (widget == dynamic_cast<RkSystemWindow*>(child))
                        return true;
        }
        return false;
}
