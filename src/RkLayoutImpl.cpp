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

RkLayoutElement::RkLayoutElement()
        : elementType{Type::Unknown}
        , elementAlignment{Alignment::Unalingned}
        , isStretchable{false}
{
}

RkLayoutElement::~RkLayoutElement()
{
}

RkLayoutElement::Alignment RkLayoutElement::alignment() const
{
        return elementAlignment;
}

void RkLayoutElement::setAlignemnt(RkLayoutElement::Alignment alignment)
{
        elementAlignment = alignment;
}

bool RkLayoutElement::stretchable() const
{
        return isStretchable;
}

void RkLayoutElement::setStretchable(bool stretchable)
{
        isStretchable = stretchable;
}

RkLayout::RkLayoutImpl::RkLayoutImpl(RkLayout* layoutInterface, RkWidget* parent)
        : inf_ptr{layoutInterface}
        , parentWidget{parent}
        , elementsPadding{0}
{
}

RkLayout::RkLayoutImpl::~RkLayoutImpl()
{
}

void RkLayout::RkLayoutImpl::setPadding(int padding)
{
        RK_UNUSED(padding);
        elementsPadding = padding;
}

int RkLayout::RkLayoutImpl::padding()
{
        return elementsPadding;
}

RkWidget* RkLayout::RkLayoutImpl::getParentWidget()
{
        return parentWidget;
}

std::list<RkLayoutElement*>& RkLayout::RkLayoutImpl::getLayoutElements()
{
        return layoutElements;
}
