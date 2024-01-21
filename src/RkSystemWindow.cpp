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
#include "RkPlatform.h"
#include "RkMain.h"
#include "RkWidgetImpl.h"

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

RkSystemWindow::RkSystemWindow(RkWidget *widget, const RkNativeWindowInfo* parent)
        : topWidget{widget}
#ifdef RK_OS_WIN
        , platformWindow{std::make_unique<RkWindowWin>(parent)}
#else // X11
        , platformWindow{std::make_unique<RkWindowX>(parent)}
#endif // X11
        , windowSize{platformWindow->size()}
        , windowBackground{platformWindow->background()}
        , isGrabKeyEnabled{false}
        , isPropagateGrabKey{true}
{
        RK_IMPL_PTR(topWidget)->setSystemWindow(this);
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
        platformWindow->show(b);
}

const RkNativeWindowInfo* RkSystemWindow::nativeWindowInfo() const
{
        return platformWindow->nativeWindowInfo();
}

RkWindowId RkSystemWindow::id() const
{
        return platformWindow->id();
}

void RkSystemWindow::setSize(const RkSize &size)
{
        platformWindow->setSize(size);
}

RkSize RkSystemWindow::size() const
{
        return platformWindow->size();
}

void RkSystemWindow::setPosition(const RkPoint &p)
{
        platformWindow->setPosition(p);
}

RkPoint RkSystemWindow::position() const
{
        return platformWindow->position();
}

void RkSystemWindow::setBackgroundColor(const RkColor &color)
{
        platformWindow->setBackgroundColor(color);
}

const RkColor& RkSystemWindow::background() const
{
        return platformWindow->background();
}

void RkSystemWindow::enableGrabKey(bool b)
{
}

bool RkSystemWindow::grabKeyEnabled() const
{
        return false; 
}

void RkSystemWindow::propagateGrabKey(bool b)
{
}

bool RkSystemWindow::propagateGrabKeyEnabled() const
{
        return false;
}

void RkSystemWindow::closeEvent([[maybe_unused]] RkCloseEvent *event)
{
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
        //        if (parentWidget())
        //                getTopWidget()->dropEvent(event);
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
        platformWindow->update();
}

//const RkCanvasInfo* RkSystemWindow::getCanvasInfo() const
//{
//       return platformWindow->getCanvasInfo();
//}

//void RkSystemWindow::freeCanvasInfo()
//{
//       return platformWindow->freeCanvasInfo();
//}

RkRect RkSystemWindow::rect() const
{
        return RkRect(0, 0, 200, 200);//  return platformWindow->rect();
}

void RkSystemWindow::close()
{
}

void RkSystemWindow::setTopWidget(RkWidget *widget)
{
        topWidget = widget;
}

RkWidget* RkSystemWindow::getTopWidget() const
{
        return topWidget;
}

void RkSystemWindow::setFocus(bool b)
{
        //impl_ptr->setFocus(b);
}

bool RkSystemWindow::hasFocus() const
{
        return true;// return impl_ptr->hasFocus();
}

void RkSystemWindow::setPointerShape(Rk::PointerShape shape)
{
        //impl_ptr->setPointerShape(shape);
}

Rk::PointerShape RkSystemWindow::pointerShape() const
{
        return Rk::PointerShape::NoShape;//impl_ptr->pointerShape();
}

void RkSystemWindow::setScaleFactor(double factor)
{
}

double RkSystemWindow::scaleFactor() const
{
        return 1.0;
}
