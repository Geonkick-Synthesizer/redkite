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
    , buttonImageState{RkButton::ButtonImage::ImageUnpressed}
    , isEmphasizeEnabled{false}
{
}

void RkButton::RkButtonImpl::setImage(const RkImage &img, RkButton::ButtonImage type)
{
        if (type != RkButton::ButtonImage::ImageUnpressed
            && type != RkButton::ButtonImage::ImageUnpressedHover
            && type != RkButton::ButtonImage::ImagePressed
            && type != RkButton::ButtonImage::ImagePressedHover) {
                return;
        }

        buttonImages[static_cast<size_t>(type)] = img;
        if (type == ButtonImage::ImageUnpressed)
                inf_ptr->setSize(img.size());
}

bool RkButton::RkButtonImpl::isPressed() const
{
        return is_pressed;
}

void RkButton::RkButtonImpl::setPressed(bool pressed)
{
        is_pressed = pressed;
        isEmphasizeEnabled = false;
        updateButtonState();
}

void RkButton::RkButtonImpl::setType(RkButton::ButtonType type)
{
        buttonType = type;
        updateButtonState();
}

RkButton::ButtonType RkButton::RkButtonImpl::type(void) const
{
        return buttonType;
}

void RkButton::RkButtonImpl::drawButton(RkPainter &painter)
{
        if (isPressed()) {
                if (!buttonImages[static_cast<size_t>(buttonImageState)].isNull())
                        painter.drawImage(buttonImages[static_cast<size_t>(buttonImageState)], 0, 0);
                else if (!buttonImages[static_cast<size_t>(RkButton::ButtonImage::ImagePressed)].isNull())
                        painter.drawImage(buttonImages[static_cast<size_t>(RkButton::ButtonImage::ImagePressed)], 0, 0);
                else if (!buttonImages[static_cast<size_t>(RkButton::ButtonImage::ImageUnpressed)].isNull())
                        painter.drawImage(buttonImages[static_cast<size_t>(RkButton::ButtonImage::ImageUnpressed)], 0, 0);
        } else if (!buttonImages[static_cast<size_t>(RkButton::ButtonImage::ImageUnpressed)].isNull()) {
                if (!buttonImages[static_cast<size_t>(buttonImageState)].isNull())
                        painter.drawImage(buttonImages[static_cast<size_t>(buttonImageState)], 0, 0);
                else
                        painter.drawImage(buttonImages[static_cast<size_t>(RkButton::ButtonImage::ImageUnpressed)], 0, 0);
        } else if (!buttonImages[static_cast<size_t>(RkButton::ButtonImage::ImageUnpressed)].isNull()) {
                painter.drawImage(buttonImages[static_cast<size_t>(RkButton::ButtonImage::ImageUnpressed)], 0, 0);
        }
}

void RkButton::RkButtonImpl::setEmphasize(bool b)
{
        isEmphasizeEnabled = b;
        updateButtonState();
}

void RkButton::RkButtonImpl::updateButtonState()
{
        if (isPressed()) {
                if (isEmphasizeEnabled)
                        buttonImageState = RkButton::ButtonImage::ImagePressedHover;
                else
                        buttonImageState = RkButton::ButtonImage::ImagePressed;
        } else {
                if (isEmphasizeEnabled)
                        buttonImageState = RkButton::ButtonImage::ImageUnpressedHover;
                else
                        buttonImageState = RkButton::ButtonImage::ImageUnpressed;
        }
}

