/**
 * File name: RkButtonImpl.h
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

#ifndef RK_LABEL_IMPL_H
#define RK_LABEL_IMPL_H

#include "RkWidgetImpl.h"
#include "RkButton.h"
#include "RkImage.h"
#include "RkPainter.h"

class RkButton::RkButtonImpl : public RkWidget::RkWidgetImpl {
 public:
        RkButtonImpl(RkButton *interface, RkWidget *parent = nullptr);
        virtual ~RkButtonImpl() = default;
        void setPressedImage(const RkImage &img);
        void setUnpressedImage(const RkImage &img);
        bool isPressed() const;
        void setPressed(bool pressed);
        ButtonType type() const;
        void setType(ButtonType type);
	void drawButton(RkPainter &painter);

 private:
        RK_DECALRE_INTERFACE_PTR(RkButton)
        ButtonType buttonType;
        bool is_pressed;
        RkImage pressedImage;
        RkImage unpressedImage;
};

#endif // RK_LABEL_H
