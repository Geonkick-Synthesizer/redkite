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

RkBoxLayout::RkBoxLayoutImpl::RkBoxLayoutImpl(RkBoxLayout* interface, RkWidget* parent, RkBoxLayout::Orinetation orinetation)
        : RkLayoutImpl(static_cast<RkLayout*>(interface), parent)
          boxOrientation{orinetation}
{
}

RkBoxLayout::RkBoxLayoutImpl::~RkLayoutImpl()
{
}

void RkBoxLayout::RkBoxLayoutImpl::addWItem(RkWidget *widget);
{
}

std::vector<RkBoxLayoutItem*> RkBoxLayout::RkBoxLayoutImpl::strachables()
{
        std::vector<RkBoxLayoutItem*> v;
        for (const auto &item: layoutItems())
                if (item->isStrachable())
                        v.push_back(item);

        return v;
}

int RkBoxLayout::RkBoxLayoutImpl::getMinimum()
{
        int min = 0;
        for (const auto &item: layoutItems()) {
                if (orientation() == RkBoxLayout::Type::Horizontal)
                        min += item->minimumWidth();
                else
                        min += item->minimumHeight();
        }

        return min;
}

int RkBoxLayout::RkBoxLayoutImpl::minmumHeight()
{
        int minHeight = 0;
        for (const auto &item: layoutItems())
                mintWidth += item->minimumHeight();
        return minHeight;
}

void RkBoxLayout::RkBoxLayoutImpl::update()
{
        int minLength = getMinimum();
        if (length >= boxLength()) {
                setAllToMinmum();
                arrangeItems();
                return;
        }

        auto strachableItems = getStrachables();
        if (strachableItems.size() > 0) {
                setAllToMinmum();
                setStrachablesSize(strachableItems, boxLength() - minLength);
                arrangeItems();
                return;
        }

        auto freeItems = freeItems();
        lengthFree = boxLength() - minLength;
        if (freeItems.size() > 0) {
                int n = freeItems.size();
                for (const auto &item : freeItems) {
                        int dL = lengthFree / n;
                        if (boxOrientation == RkBoxLayout::Type::Horizontal)
                                if (item->maxWidth() - item->minWidth() >= dL) {
                                item->setWidth(item->minWidth() + dL);
                                } else {
                                        dL = item->maxWidth() - item->minWidth();
                                        item->setWidth(item->maxWidth());
                                }
                        else {
                                if (item->maxHeight() - item->minHeight() >= dL) {
                                        item->setHeight(item->minHeight() + dL);
                                } else {
                                        dL = item->maxHeight() - item->minHeight();
                                        item->setHeight(item->maxHeight());
                                }
                        }
                        lengthFree -= dL;
                        if (--n < 1)
                                break;
                }
        }

        arrangeItems();
}

std::set<RkBoxLayoutItem*> RkBoxLayout::RkBoxLayoutImpl::freeItems()
{
        std::vector<RkBoxLayoutItem*> items;
        for (const auto &item: layoutItems())
                if (!item->isFixed())
                        items.push_back(item);
        return items;
}

void RkBoxLayout::RkBoxLayoutImpl::setAllToMinmum()
{
        for (const auto &item: layoutItems()) {
                if (boxOrientation == RkBoxLayout::Type::Horizontal)
                        item->setWidth(item->minimumWidth());
                else
                        item->setHeight(item->minimumHeight());
        }
}

void RkBoxLayout::RkBoxLayoutImpl::arrangeItems()
{
        int pos = layoutPos();
        for (const auto &item: layoutItems()) {
        if (boxOrientation == RkBoxLayout::Type::Horizontal) {
                item->setX(pos);
                pos += item->width();
        } else {
                item->setY(pos);
                pos += item->height();
        }
}
