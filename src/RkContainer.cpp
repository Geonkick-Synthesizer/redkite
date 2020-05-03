/**
 * File name: RkWidgetContainer.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor <http://geontime.com>
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

#include "RkContainer.h"
#include "RkContainerWidgetItem.h"

RkWidgetContainer::RkContainer(RkContinerItem *parent, Rk::Orientation orientation)
	: RkContinerItem(parent, ItemType::ItemContiner)
	, containerOrientation{orientation}
	, itemSpacing{0}
{
	setSize(parent->size());
}

void RkWidgetContainer::addContiner(RkWidgetContiner *continer, Rk::Alignment align)
{
        continer.setAlignment(align);
	continerItems.push_back(continer);
	update();
}

void RkWidgetContainer::addWidget(RkWidget *widget, Rk::Alignment align)
{
        auto item = RkContinerWidgetItem(widget, align);
	continerItems.push_back(item);
	update();
}

void RkWidgetContainer::removeWidget(RkWidget *widget)
{
}

void RkWidgetContainer::addSpace(int space, Rk::Alignment align)
{
        auto item = new RkContinerItem(this, RkContinerItem::ItemType::ItemSpace, align);
        item->setSize({space, space});
        continerItems.push_back(item);
	update();
}

void RkWidgetContainer::removeAt(size_t index)
{
        if (index < continerItems.size()) {
                if (continerItems[index]->parent() == this)
                        delete continerItems[index];
                continerItems.erase(continerItems.begin() + index);
        }
}

RkContinerItem* RkWidgetContainer::at(size_t index) const
{
        if (index < continerItems.size())
                return continerItems[index];
        return nullptr;
}

void RkWidgetContainer::update()
{
	int posLeft = initPosition(Rk::Alignment::AlignLeft);
	int posRight = initPosition(Rk::Alignment::AlignRight);
	for (const auto &item: continerItems) {
                auto align = item->alignment();
                if (orientation() == Rk::Orientation::Horizontal) {
                        (align == Rk::Alignment::AlignLeft || align == Rk::Alignment::AlignTop) ?
                                item->setX(posLeft) : item->setX(posRight - item->width());
                        item->setY((height() - item->height()) / 2);
                } else {
                        (align == Rk::Alignment::AlignLeft || align == Rk::Alignment::AlignTop) ?
                                item->setY(posLeft) : item->setY(posRight - item->height());
                        item->setX((width() - item->width()) / 2);
                }

                auto w = (orientation() == Rk::Orientation::Horizontal) ? item->width() : item->height();
                if (align == Rk::Alignment::AlignLeft || align == Rk::Alignment::AlignTop)
                        posLeft += w + itemSpacing;
                else
                        posRight -= w + itemSpacing;
	}
}

int RkWidgetContainer::initPosition(Rk::Alignment alignment)
{
	int pos = 0;
	if (alignment == Rk::Alignment::AlignLeft) {
		if (orientation() == Rk::Orientation::Horizontal)
			pos = containerPosition.x();
		else
			pos = containerPosition.y();
	} else {
		if (orientation() == Rk::Orientation::Horizontal)
			pos = containerPosition.x() + width();
		else
			pos = containerPosition.y() + height();
	}
	return pos;
}

void RkWidgetContainer::clear()
{
        std::erase(std::remove_if(continerItems.begin(),
                                  continerItems.end,
                                  [&](RkContinerItem *item){
                                          if (item->parent() == this)
                                                  delete item;
                                          return true;
                                  }),
                   continerItems.end());
}

Rk::Orientation RkWidgetContainer::orientation() const
{
	return containerOrientation;
}

void RkWidgetContainer::setSize(const RkSize &size)
{
        RkContainerItem::setSize(size);
	update();
}

void RkWidgetContainer::setWidth(int width)
{
	RkContainerItem::setWidth(width);
	update();
}

void RkWidgetContainer::setHeight(int height)
{
	RkContainerItem::setHeight(height);
	update();
}

void RkWidgetContainer::setPosition(const RkPoint &position)
{
        RkContainerItem::setPosition(position);
	update();
}

void RkWidgetContainer::setX(int val)
{
        RkContainerItem::setX(val);
        update();
}

void RkWidgetContainer::setY(int val)
{
        RkContainerItem::setY(val);
        update();
}

void RkWidgetContainer::setSpacing(size_t space)
{
	itemSpacing = space;
	update();
}

size_t RkWidgetContainer::spacing() const
{
	return itemSpacing;
}
