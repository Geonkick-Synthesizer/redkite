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

#include "RkWidgetContainer.h"

RkWidgetContainer::RkWidgetContainer(RkWidget *parent, Rk::Orientation orientation)
	: parentWidget{parent}
	, containerOrientation{orientation}
	, idGenerator{0}
	, widgetsSpacing{0}
{
	setSize(parentWidget->size());
}

void RkWidgetContainer::addWidget(RkWidget *widget, Rk::Alignment align)
{
	if (idGenerator > 1000000)
		return;
	idGenerator++;
	itemsIds.push_back(idGenerator);
	widgets.insert({idGenerator, {static_cast<int>(align), widget}});
	update();
}

void RkWidgetContainer::removeWidget(RkWidget *widget)
{
}

void RkWidgetContainer::addSpace(RkWidgetContainerSpace space, Rk::Alignment align)
{
	if (idGenerator > 1000000)
		return;
	idGenerator++;
	itemsIds.push_back(idGenerator);
	spaces.insert({idGenerator, {static_cast<int>(align), space}});
	update();
}

void RkWidgetContainer::removeAt(size_t index)
{
}

void RkWidgetContainer::update()
{
	int posLeft = initPosition(Rk::Alignment::AlignLeft);
	int posRight = initPosition(Rk::Alignment::AlignRight);
	for (const auto &id: itemsIds) {
		auto resWidget = widgets.find(id);
		if (resWidget != widgets.end() && resWidget->second.second->isShown()) {
			auto widget = resWidget->second.second;
			auto align = static_cast<Rk::Alignment>(resWidget->second.first);
			if (orientation() == Rk::Orientation::Horizontal) {
				(align == Rk::Alignment::AlignLeft || align == Rk::Alignment::AlignTop) ?
					widget->setX(posLeft) : widget->setX(posRight - widget->width());
				widget->setY((height() - widget->height()) / 2);
			} else {
				(align == Rk::Alignment::AlignLeft || align == Rk::Alignment::AlignTop) ?
					widget->setY(posLeft) : widget->setY(posRight - widget->height());
				widget->setX((width() - widget->width()) / 2);
			}

			auto w = (orientation() == Rk::Orientation::Horizontal) ? widget->width() : widget->height();
			if (align == Rk::Alignment::AlignLeft || align == Rk::Alignment::AlignTop)
				posLeft += w + widgetsSpacing;
			else
				posRight -= w + widgetsSpacing;
		}

		auto resSpace = spaces.find(id);
		if (resSpace != spaces.end()) {
			auto space = resSpace->second.second;
			auto align = static_cast<Rk::Alignment>(resSpace->second.first);
			if (align == Rk::Alignment::AlignLeft || align == Rk::Alignment::AlignTop)
				posLeft += space;
			else
				posRight -= space;
		}
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
	itemsIds.clear();
	widgets.clear();
	spaces.clear();
	idGenerator = 0;
}

Rk::Orientation RkWidgetContainer::orientation() const
{
	return containerOrientation;
}

Rk::Alignment RkWidgetContainer::alignment(RkWidget *widget) const
{
	return Rk::Alignment::AlignLeft;
}

Rk::Alignment RkWidgetContainer::alignment(size_t index) const
{
	return Rk::Alignment::AlignLeft;
}

void RkWidgetContainer::setSize(const RkSize &size)
{
	containerSize = size;
	update();
}

RkSize RkWidgetContainer::size() const
{
	return containerSize;
}

int RkWidgetContainer::width() const
{
	return containerSize.width();
}

void RkWidgetContainer::setWidth(int width)
{
	containerSize.setWidth(width);
	update();
}

int RkWidgetContainer::height() const
{
	return 	containerSize.height();
}

void RkWidgetContainer::setHeight(int height)
{
	containerSize.setHeight(height);
	update();
}

void RkWidgetContainer::setPosition(const RkPoint &position)
{
	containerPosition = position;
	update();
}

RkPoint RkWidgetContainer::position() const
{
	return containerPosition;
}

void RkWidgetContainer::setSpacing(size_t space)
{
	widgetsSpacing = space;
	update();
}

size_t RkWidgetContainer::spacing() const
{
	return widgetsSpacing;
}
