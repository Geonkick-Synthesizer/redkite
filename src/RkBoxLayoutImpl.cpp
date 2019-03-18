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

#include "RkBoxLayoutImpl.h"

RkBoxLayoutWidgetElement::RkBoxLayoutWidgetElement(RkWidget* widget)
        : elementWidget{widget}
{
}

RkBoxLayoutWidgetElement::~RkBoxLayoutWidgetElement()
{
}

RkLayoutElement::Type RkBoxLayoutWidgetElement::type() const
{
        return RkLayoutElement::Type::BoxWidget;
}

int RkBoxLayoutWidgetElement::minimumWidth() const
{
        return elementWidget->minimumWidth();
}

int RkBoxLayoutWidgetElement::maximumWidth() const
{
        return elementWidget->maximumWidth();
}

int RkBoxLayoutWidgetElement::minimumHeight() const
{
        return elementWidget->minimumHeight();
}

int RkBoxLayoutWidgetElement::maximumHeight() const
{
        return elementWidget->maximumHeight();
}

void RkBoxLayoutWidgetElement::setSize(const std::pair<int, int> &size)
{
        elementWidget->setSize(size);
}

int RkBoxLayoutWidgetElement::width() const
{
        return elementWidget->width();
}

int RkBoxLayoutWidgetElement::height() const
{
        return elementWidget->height();
}

void RkBoxLayoutWidgetElement::setWidth(int width)
{
        elementWidget->setWidth(width);
}

void RkBoxLayoutWidgetElement::setHeight(int height)
{
        elementWidget->setWidth(height);
}

RkWidget* RkBoxLayoutWidgetElement::widget()
{
        return elementWidget;
}

bool RkBoxLayoutWidgetElement::fixedWidth() const
{
        return false;
}

bool RkBoxLayoutWidgetElement::fixedHeight() const
{
        return false;
}

RkBoxLayout::RkBoxLayoutImpl::RkBoxLayoutImpl(RkBoxLayout* interface,
                                              RkWidget* parent,
                                              RkBoxLayout::Orientation orientation)
        : RkLayoutImpl(static_cast<RkLayout*>(interface), parent)
        , boxOrientation{orientation}
{
}

RkBoxLayout::RkBoxLayoutImpl::~RkBoxLayoutImpl()
{
}

std::vector<RkBoxLayoutWidgetElement*> RkBoxLayout::RkBoxLayoutImpl::stretchables() const
{
        std::vector<RkBoxLayoutWidgetElement*> v;
        for (const auto &element: getLayoutElements())
                if (element->stretchable())
                        v.push_back(dynamic_cast<RkBoxLayoutWidgetElement*>(element));

        return v;
}

void RkBoxLayout::RkBoxLayoutImpl::addWidget(RkWidget *widget)
{
        addElement(static_cast<RkLayoutElement*>(new RkBoxLayoutWidgetElement(widget)));
}

void RkBoxLayout::RkBoxLayoutImpl::setOrientation(Orientation orientation)
{
        boxOrientation = orientation;
}

Orientation RkBoxLayout::RkBoxLayoutImpl::orientation()
{
        return boxOrientation;
}

int RkBoxLayout::RkBoxLayoutImpl::getMinimum()
{
        int min = 0;
        for (const auto &element: layoutElements()) {
                if (orientation() == RkBoxLayout::Type::Horizontal)
                        min += element->minimumWidth();
                else
                        min += element->minimumHeight();
        }

        return min;
}

int RkBoxLayout::RkBoxLayoutImpl::minmumHeight()
{
        int minHeight = 0;
        for (const auto &element: layoutElements())
                mintWidth += element->minimumHeight();
        return minHeight;
}

void RkBoxLayout::RkBoxLayoutImpl::update()
{
        int minLength = getMinimum();
        if (length >= boxLength()) {
                setAllToMinmum();
                arrangeElements();
                return;
        }

        auto strachableElements = getStrachables();
        if (strachableElements.size() > 0) {
                setAllToMinmum();
                setStrachablesSize(strachableElements, boxLength() - minLength);
                arrangeElements();
                return;
        }

        auto freeElements = freeElements();
        lengthFree = boxLength() - minLength;
        if (freeElements.size() > 0) {
                int n = freeElements.size();
                for (const auto &element : freeElements) {
                        int dL = lengthFree / n;
                        if (boxOrientation == RkBoxLayout::Type::Horizontal)
                                if (element->maxWidth() - element->minWidth() >= dL) {
                                element->setWidth(element->minWidth() + dL);
                                } else {
                                        dL = element->maxWidth() - element->minWidth();
                                        element->setWidth(element->maxWidth());
                                }
                        else {
                                if (element->maxHeight() - element->minHeight() >= dL) {
                                        element->setHeight(element->minHeight() + dL);
                                } else {
                                        dL = element->maxHeight() - element->minHeight();
                                        element->setHeight(element->maxHeight());
                                }
                        }
                        lengthFree -= dL;
                        if (--n < 1)
                                break;
                }
        }

        arrangeElements();
}

std::set<RkBoxLayoutElement*> RkBoxLayout::RkBoxLayoutImpl::freeElements()
{
        std::vector<RkBoxLayoutElement*> elements;
        for (const auto &element: getLayoutElements()) {
                if (orientation() == RkBoxLayout::Orientation::Horizontal && element->fixedWith()
                    || orientation() == RkBoxLayout::Orientation::Vertical && element->fixedHeight())
                        elements.push_back(element);
        }
        return elements;
}

void RkBoxLayout::RkBoxLayoutImpl::setAllToMinmum()
{
        for (const auto &element: getLayoutElements()) {
                if (boxOrientation == RkBoxLayout::Type::Horizontal)
                        element->setWidth(element->minimumWidth());
                else
                        element->setHeight(element->minimumHeight());
        }
}

void RkBoxLayout::RkBoxLayoutImpl::arrangeElements()
{
        int pos = layoutPos();
        for (const auto &element: getLayoutElements()) {
        if (boxOrientation == RkBoxLayout::Type::Horizontal) {
                element->setX(pos);
                pos += element->width();
        } else {
                element->setY(pos);
                pos += element->height();
        }
}

int RkBoxLayout::RkBoxLayoutImpl::boxLength()
{
        if (boxOrientation == RkBoxLayout::Type::Horizontal)
                return getParentWidget()->width();
        else
                return getParentWidget()->height();
}
