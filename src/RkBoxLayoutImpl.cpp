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
        for (const auto &item: layoutItems)
                if (item->isStrachable())
                        v.push_back(item);

        return v;
}

void RkBoxLayout::RkBoxLayoutImpl::update()
{
        int minWidth = minmumWidth();
        if (minWidth >= layoutWidth()) {
                setAllToMinmum();
                arrangeItems();
                return;
        }

        auto strachableItems = getStrachables();
        if (strachableItems.size() > 0) {
                setAllToMinmum();
                setStrachablesSize(strachableItems, layoutWidth() - minwidth);
                arrangeItems();
                return;
        }
                setStachablesWidth();

        auto freeItems = freeItems();
        if (freeItems.size() > 0) {
                int n = freeItems.size();
                for (const auto &item : freeItems) {
                        int dW = widthFree / n;
                        if (item->maxWidth() - item->minWidth() >= dW) {
                                item->setWidth(item->minWidth() + dW);
                        } else {
                           dW = item->maxWidth() - item->minWidth();
                           item->setWidth(item->maxWidth());
                        }
                        widthFree -= dW;
                        if (--n < 1)
                                break;
                }
        }

        arrangeItems();
}
