/**
 * File name: RkButtonImpl.cpp
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

#include "RkButtonImpl.h"

RkButton::RkButtonImpl::RkButtonImpl(RkButton *interface, RkWidget *parent)
    : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
    , inf_ptr{interface}
    , is_pressed{false}
    , is_checkable{false}
{
}

void RkButton::RkButtonImpl::setPressedImage(const RkImage &img)
{
        pressedImage = img;
	inf_ptr->setFixedSize(img.width(), img.height());
}

void RkButton::RkButtonImpl::setUnpressedImage(const RkImage &img)
{
        unpressedImage = img;
	inf_ptr->setFixedSize(img.width(), img.height());
}

bool RkButton::RkButtonImpl::isPressed() const
{
        return is_pressed;
}

bool RkButton::RkButtonImpl::isCheckable()
{
        return is_checkable;
}

void RkButton::RkButtonImpl::setPressed(bool pressed)
{
        is_pressed = pressed;
}

void RkButton::RkButtonImpl::setCheckable(bool checkable)
{
        is_checkable = checkable;
}

void RkButton::RkButtonImpl::drawButton(RkPainter &painter)
{
        if (isPressed())
                painter.drawImage(pressedImage, 0, 0);
	else
		painter.drawImage(unpressedImage, 0, 0);
}
