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
#include "RkLog.h"

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
        elementWidget->setHeight(height);
}

void RkBoxLayoutWidgetElement::setX(int val)
{
        elementWidget->setX(val);
}

void RkBoxLayoutWidgetElement::setY(int val)
{
        elementWidget->setY(val);
}

int RkBoxLayoutWidgetElement::x() const
{
        return elementWidget->x();
}

int RkBoxLayoutWidgetElement::y() const
{
        return elementWidget->y();
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

std::vector<RkLayoutElement*> RkBoxLayout::RkBoxLayoutImpl::stretchables() const
{
        std::vector<RkLayoutElement*> v;
        for (const auto &element: getLayoutElements())
                if (element->stretchable())
                        v.push_back(element);

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

RkBoxLayout::Orientation RkBoxLayout::RkBoxLayoutImpl::orientation() const
{
        return boxOrientation;
}

int RkBoxLayout::RkBoxLayoutImpl::getMinimum() const
{
        int min = 0;
        for (const auto &element: getLayoutElements()) {
                if (orientation() == RkBoxLayout::Orientation::Horizontal)
                        min += element->minimumWidth();
                else
                        min += element->minimumHeight();
        }

        return min;
}

void RkBoxLayout::RkBoxLayoutImpl::setStretchablesSize(const std::vector<RkLayoutElement*> &stretchableElements, int size)
{
        for (const auto &element: stretchableElements) {
                if (orientation() == RkBoxLayout::Orientation::Horizontal)
                        element->setWidth(size);
                else
                        element->setHeight(size);
        }
}

void RkBoxLayout::RkBoxLayoutImpl::update()
{
        int minLength = getMinimum();
        if (minLength >= boxLength()) {
                setAllToMinmum();
                arrangeElements();
                return;
        }

        auto stretchableElements = stretchables();
        if (stretchableElements.size() > 0) {
                setAllToMinmum();
                setStretchablesSize(stretchableElements, boxLength() - minLength);
                arrangeElements();
                return;
        }

        auto freeElements = getFreeElements();
        int lengthFree = boxLength() - minLength;
        if (!freeElements.empty()) {
                int n = freeElements.size();
                for (const auto &element : freeElements) {
                        int dL = lengthFree / n;
                        if (boxOrientation == RkBoxLayout::Orientation::Horizontal) {
                                if (element->maximumWidth() - element->minimumWidth() >= dL) {
                                        element->setWidth(element->minimumWidth() + dL);
                                } else {
                                        dL = element->maximumWidth() - element->minimumWidth();
                                        element->setWidth(element->maximumWidth());
                                }
                        } else {
                                if (element->maximumHeight() - element->minimumHeight() >= dL) {
                                        element->setHeight(element->minimumHeight() + dL);
                                } else {
                                        dL = element->maximumHeight() - element->minimumHeight();
                                        element->setHeight(element->maximumHeight());
                                }
                        }
                        lengthFree -= dL;
                        if (--n < 1)
                                break;
                }
        }

        arrangeElements();
}

std::vector<RkLayoutElement*> RkBoxLayout::RkBoxLayoutImpl::getFreeElements()
{
        std::vector<RkLayoutElement*> elements;
        for (const auto &element: getLayoutElements()) {
                if ((orientation() == RkBoxLayout::Orientation::Horizontal && !element->fixedWidth())
                    || (orientation() == RkBoxLayout::Orientation::Vertical && !element->fixedHeight()))
                        elements.push_back(element);
        }
        return elements;
}

void RkBoxLayout::RkBoxLayoutImpl::setAllToMinmum()
{
        for (const auto &element: getLayoutElements()) {
                if (boxOrientation == RkBoxLayout::Orientation::Horizontal)
                        element->setWidth(element->minimumWidth());
                else
                        element->setHeight(element->minimumHeight());
        }
}

void RkBoxLayout::RkBoxLayoutImpl::arrangeElements()
{
        int pos = (boxOrientation == RkBoxLayout::Orientation::Horizontal) ? x() : y();
        for (const auto &element: getLayoutElements()) {
                if (boxOrientation == RkBoxLayout::Orientation::Horizontal) {
                        element->setX(pos);
                        element->setHeight(height());
                        pos += element->width();
                } else {
                        element->setY(pos);
                        element->setWidth(width());
                        pos += element->height();
                }
        }
}

int RkBoxLayout::RkBoxLayoutImpl::boxLength() const
{
        if (boxOrientation == RkBoxLayout::Orientation::Horizontal)
                return width();
        else
                return height();
}

