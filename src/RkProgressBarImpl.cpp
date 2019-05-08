/**
 * File name: RkProgressBarImpl.cpp
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

#include "RkProgressBarImpl.h"
#include "RkPainter.h"
#include "RkLog.h"

RkProgressBar::RkProgressBarImpl::RkProgressBarImpl(RkProgressBar *interface, RkWidget *parent)
    : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
    , inf_ptr{interface}
    , minimumValue{0}
    , maximumValue{100}
    , currentValue{0}
    , progressColor{0}
    , progressOrientation{Rk::Orientation::Horizontal}
{
}

RkProgressBar::RkProgressBarImpl::~RkProgressBarImpl()
{
}


int RkProgressBar::RkProgressBarImpl::minVal() const
{
        return minimumValue;
}

void RkProgressBar::RkProgressBarImpl::setMinVal(int val) const
{
        minimumValue = val;
}

int RkProgressBar::RkProgressBarImpl::maxVal() const
{
        return maximumValue;
}

int RkProgressBar::RkProgressBarImpl::setMaxVal(int val)
{
        maximumValue = val;
}

Rk::Orinetation RkProgressBar::RkProgressBarImpl::orientation() const
{
        return progressOrientation;
}

void RkProgressBar::RkProgressBarImpl::setOrientation(Rk::Orientation orientation)
{
        progressOrientation  = orientation;
}

int RkProgressBar::RkProgressBarImpl::value(Rk::Orientation orientation) const
{
        return currentValue;
}

void RkProgressBar::RkProgressBarImpl::setValue(int val)
{
        currentValue = val;
}

void RkProgressBar::RkProgressBarImpl::setProgressColor(const RkColor &color)
{
        progressColor = color;
}

void RkProgressBar::RkProgressBarImpl::drawProgressBar()
{
        RkImage img(width(), height());
        RkPainter painter(&img);
        painter.fillRect(rect(), background());
        int range = maximumValue - minimumValue;
        if (range > 0) {
                if (progressOrientation == Rk::Orientation::Horizontal)
                        painter.fillRect(RkRect(0, 0, currentValue * width() / range, height()), background());
                else
         }
}

