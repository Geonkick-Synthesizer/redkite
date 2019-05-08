/**
 * File name: RkProgressBar.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://quamplex.com>
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

#include "RkProgressBar.h"
#include "RkProgressBarImpl.h"
#include "RkLog.h"

RkProgressBar::RkProgressBar(RkWidget *parent)
        : RkWidget(parent, std::static_pointer_cast<RkProgressBar::RkWidgetImpl>(std::make_shared<RkProgressBar::RkProgressBarImpl>(this, parent)))
        , impl_ptr{std::static_pointer_cast<RkProgressBar::RkProgressBarImpl>(o_ptr)}
{
}

int RkProgressBar::maximumValue() const
{
        return impl_ptr->maxVal();
}

void RkProgressBar::setMaximum(int maximum)
{
        impl_ptr->setMaxVal(maximum);
        update();
}

int RkProgressBar::minimumValue() const
{
        return impl_ptr->minVal();
}

void RkProgressBar::setMinimum(int minimum)
{
        impl_ptr->setMinVal(minimum);
        update();
}

void RkProgressBar::setRange(int minimum, int maximum)
{
        impl_ptr->setMinVal(minimum);
        impl_ptr->setMaxVal(minimum);
        update();
}

Rk::Orientation RkProgressBar::orientation() const
{
        return impl_ptr->orientation();
}

void RkProgressBar::setOrientation(Rk::Orientation orientation)
{
        impl_ptr->setOrientation(orientation);
        update();
}

int RkProgressBar::value() const
{
        return impl_ptr->value();
}

void RkProgressBar::setValue(int value)
{
        impl_ptr->setValue(value);
        update();
}

void RkProgressBar::reset()
{
        setValue(minimumValue());
}

void RkProgressBar::setProgressColor(const RkColor &color)
{
        impl_ptr->setProgressColor(color);
        update();
}

void RkProgressBar::paintEvent(const std::shared_ptr<RkPaintEvent> &event)
{
        impl_ptr->drawProgressBar();
}
