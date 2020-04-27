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
    , buttonType{ButtonType::ButtonUncheckable}
    , is_pressed{false}
    , is_emphasizeEnabled{true}
    , is_emphasize{false}
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

void RkButton::RkButtonImpl::setPressed(bool pressed)
{
        is_pressed = pressed;
}

void RkButton::RkButtonImpl::setType(RkButton::ButtonType type)
{
        buttonType = type;
}

RkButton::ButtonType RkButton::RkButtonImpl::type(void) const
{
        return buttonType;
}

void RkButton::RkButtonImpl::drawButton(RkPainter &painter)
{
        painter.fillRect(inf_ptr->rect(), inf_ptr->background());
        if (isPressed() && !pressedImage.isNull()) {
                if (isEmphasize()) {
                        RkImage img;
                        img = pressedImage;
                        applyEffect(img);
                        painter.drawImage(img, 0, 0);
                } else {
                        painter.drawImage(pressedImage, 0, 0);
                }
        } else if (!unpressedImage.isNull()) {
                if (isEmphasize()) {
                        RkImage img;
                        img = unpressedImage;
                        applyEffect(img);
                        painter.drawImage(img, 0, 0);
                } else {
                        painter.drawImage(unpressedImage, 0, 0);
                }
        }
}

void RkButton::RkButtonImpl::applyEffect(RkImage &img)
{
        RkPainter paint(&img);
        paint.applyAlpha(50);
}

void RkButton::RkButtonImpl::setEmphasize(bool b)
{
        is_emphasize = b;
}

bool RkButton::RkButtonImpl::isEmphasize() const
{
        return is_emphasizeEnabled && is_emphasize;
}

void RkButton::RkButtonImpl::enableEmphasize(bool b)
{
        is_emphasizeEnabled = b;
}

bool RkButton::RkButtonImpl::emphasizeEnabled() const
{
        return is_emphasizeEnabled;
}

