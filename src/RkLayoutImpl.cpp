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
        , layoutPosition{0, 0}
        , layoutSize{parent->size()}

{
}

RkLayout::RkLayoutImpl::~RkLayoutImpl()
{
}

void RkLayout::RkLayoutImpl::addElement(RkLayoutElement* element)
{
        if (element && !elementExists(element))
                layoutElements.push_back(element);
}

bool RkLayout::RkLayoutImpl::elementExists(const RkLayoutElement* element) const
{
        for (const auto &e: layoutElements)
                if (e == element)
                        return true;
        return false;
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

RkWidget* RkLayout::RkLayoutImpl::getParentWidget() const
{
        return parentWidget;
}

const std::list<RkLayoutElement*>& RkLayout::RkLayoutImpl::getLayoutElements() const
{
        return layoutElements;
}

void RkLayout::RkLayoutImpl::update()
{
}

int RkLayout::RkLayoutImpl::x() const
{
        return layoutPosition.first;
}

int RkLayout::RkLayoutImpl::y() const
{
        return layoutPosition.second;
}

int RkLayout::RkLayoutImpl::width() const
{
        return layoutSize.first;
}

int RkLayout::RkLayoutImpl::height() const
{
        return layoutSize.second;
}

void RkLayout::RkLayoutImpl::setSize(const std::pair<int, int> &size)
{
        layoutSize = size;
        update();
}

std::pair<int, int> RkLayout::RkLayoutImpl::size(void) const
{
        return layoutSize;
}
