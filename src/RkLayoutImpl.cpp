/**
 * File name: RkLayoutImpl.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor (http://quamplex.com/redkite)
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

#include "RkLayoutImpl.h"

RkLayout::RkLayoutImpl::RkLayoutImpl(RkLayout* layoutInterface, RkWidget* parent)
        : inf_ptr{layoutInterface}
        , parentWidget{parent}
{
}

RkLayout::RkLayoutImpl::~RkLayoutImpl()
{
}

void RkLayout::RkLayoutImpl::addWidget(RkWidget *widget)
{
        for (const auto &w : layoutWidgets) {
                if (w == widget)
                        return;
        }

        
        layoutWidget.push_back(widget);
        update();
}

void RkLayout::RkLayoutImpl::setPadding(int padding)
{
        RK_UNUSED(padding);
}

RkLayoutItem* RkLayout::RkLayoutImpl::createItem(RkWidget *widget)
{
        return new RkLayoutItem(RkLayoutItem::Type::Widget);
}

