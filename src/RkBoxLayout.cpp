/**
 * File name: RkBoxLayout.cpp
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

#include "RkLog.h"
#include "RkBoxLayout.h"
#include "RkBoxLayoutImpl.h"

RkBoxLayout::RkBoxLayout(RkWidget *parent, Orientation orientation)
        : RkLayout(parent, std::static_pointer_cast<RkLayout::RkLayoutImpl>(std::make_shared<RkBoxLayoutImpl>(this, parent, orientation)))
        , impl_ptr{std::static_pointer_cast<RkBoxLayout::RkBoxLayoutImpl>(o_ptr)}
{
}

RkBoxLayout::~RkBoxLayout()
{
}

void RkBoxLayout::addWidget(RkWidget *widget)
{
        impl_ptr->addWidget(widget);
        update();
}

void RkBoxLayout::setOrientation(RkBoxLayout::Orientation orientation)
{
        impl_ptr->setOrientation(orientation);
}

RkBoxLayout::Orientation RkBoxLayout::orientation()
{
        return impl_ptr->orientation();
}

void RkBoxLayout::update()
{
        impl_ptr->update();
}

