/**
 * File name: RkButton.cpp
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

#include "RkButton.h"
#include "RkButtonImpl.h"
#include "RkPainter.h"

RkButton::RkButton(RkWidget *parent)
        : RkWidget(parent, std::static_pointer_cast<RkButton::RkWidgetImpl>(std::make_shared<RkButton::RkButtonImpl>(this, parent)))
        , impl_ptr{std::static_pointer_cast<RkButton::RkButtonImpl>(o_ptr)}
{
        if (parent)
                setBackgroundColor(parent->background());
}

void RkButton::setPressedImage(const RkImage &img)
{
        impl_ptr->setPressedImage(img);
        update();
}

void RkButton::setUnpressedImage(const RkImage &img)
{
        impl_ptr->setUnpressedImage(img);
        update();
}

bool RkButton::isPressed() const
{
	return impl_ptr->isPressed();
}

void RkButton::setPressed(bool pressed)
{
        impl_ptr->setPressed(pressed);
        update();
}

void RkButton::setCheckable(bool b)
{
        setType(b ? ButtonType::ButtonCheckable : ButtonType::ButtonUncheckable);
}

bool RkButton::isCheckable() const
{
        return type() == ButtonType::ButtonCheckable;
}

RkButton::ButtonType RkButton::type() const
{
        return impl_ptr->type();
}

void RkButton::setType(RkButton::ButtonType type)
{
        impl_ptr->setType(type);
        update();
}

void RkButton::mouseButtonPressEvent(RkMouseEvent *event)
{
        RK_UNUSED(event);
        if (type() == ButtonType::ButtonCheckable) {
                setPressed(!isPressed());
                action toggled(isPressed());
        } else if ((type() == ButtonType::ButtonUncheckable || type() == ButtonType::ButtonPush)
                   && !isPressed()) {
                setPressed(true);
                action toggled(true);
        }
}

void RkButton::mouseButtonReleaseEvent(RkMouseEvent *event)
{
        if (type() == ButtonType::ButtonPush)
                setPressed(false);
}

void RkButton::paintEvent(RkPaintEvent *event)
{
	RK_UNUSED(event);
        RkPainter painter(this);
        impl_ptr->drawButton(painter);
}
