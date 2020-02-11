/**
 * File name: RkButton.h
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

#ifndef RK_BUTTON_H
#define RK_BUTTON_H

#include "RkWidget.h"
#include "RkImage.h"

class RkButton: public RkWidget
{
 public:
        explicit RkButton(RkWidget *parent);
        virtual ~RkButton() = default;
        void setPressedImage(const RkImage &img);
        void setUnpressedImage(const RkImage &img);
        bool isPressed() const;
        bool isCheckable() const;
        void setPressed(bool pressed);
        void setCheckable(bool checkable);
        RK_DECL_ACT(toggled, toggled(bool pressed), RK_ARG_TYPE(bool), RK_ARG_VAL(pressed));

 protected:
        RK_DELCATE_IMPL_PTR(RkButton)
        void mouseButtonPressEvent(const std::shared_ptr<RkMouseEvent> &event) override;
        void paintEvent(const std::shared_ptr<RkPaintEvent> &event) override;
};

#endif // RK_BUTTON_H
