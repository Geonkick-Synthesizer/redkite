/**
 * File name: RkWidgetContiner.cpp
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

#include "RkWidgetContiner.h"

RkWidgetContiner::RkWidgetContiner(RkWidget *parent, Rk::Orientation orientation)
	: parentWidget{parent}
	, continerOrientation{orientation}
	, idGenerator{0}
	, widgetsSpacing{0}
{
	setSize(parentWidget->size());
}

void RkWidgetContiner::addWidget(RkWidget *widget, Rk::Alignment align)
{
	if (idGenerator > 1000000)
		return;
	idGenerator++;
	itemsIds.push_back(idGenerator);
	widgets.insert({idGenerator, {static_cast<int>(align), widget}});
	update();
}

void RkWidgetContiner::removeWidget(RkWidget *widget)
{
}

void RkWidgetContiner::addSpace(RkWidgetContinerSpace space, Rk::Alignment align)
{
	if (idGenerator > 1000000)
		return;
	idGenerator++;
	itemsIds.push_back(idGenerator);
	spaces.insert({idGenerator, {static_cast<int>(align), space}});
	update();
}

void RkWidgetContiner::removeAt(size_t index)
{
}

void RkWidgetContiner::update()
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

int RkWidgetContiner::initPosition(Rk::Alignment alignment)
{
	int pos = 0;
	if (alignment == Rk::Alignment::AlignLeft) {
		if (orientation() == Rk::Orientation::Horizontal)
			pos = continerPosition.x();
		else
			pos = continerPosition.y();
	} else {
		if (orientation() == Rk::Orientation::Horizontal)
			pos = continerPosition.x() + width();
		else
			pos = continerPosition.y() + height();
	}
	return pos;
}

void RkWidgetContiner::clear()
{
	itemsIds.clear();
	widgets.clear();
	spaces.clear();
	idGenerator = 0;
}

Rk::Orientation RkWidgetContiner::orientation() const
{
	return continerOrientation;
}

Rk::Alignment RkWidgetContiner::alignment(RkWidget *widget) const
{
	return Rk::Alignment::AlignLeft;
}

Rk::Alignment RkWidgetContiner::alignment(size_t index) const
{
	return Rk::Alignment::AlignLeft;
}

void RkWidgetContiner::setSize(const RkSize &size)
{
	continerSize = size;
	update();
}

RkSize RkWidgetContiner::size() const
{
	return continerSize;
}

int RkWidgetContiner::width() const
{
	return continerSize.width();
}

void RkWidgetContiner::setWidth(int width)
{
	continerSize.setWidth(width);
	update();
}

int RkWidgetContiner::height() const
{
	return 	continerSize.height();
}

void RkWidgetContiner::setHeight(int height)
{
	continerSize.setHeight(height);
	update();
}

void RkWidgetContiner::setPosition(const RkPoint &position)
{
	continerPosition = position;
	update();
}

RkPoint RkWidgetContiner::position() const
{
	return continerPosition;
}

void RkWidgetContiner::setSpacing(size_t space)
{
	widgetsSpacing = space;
	update();
}

size_t RkWidgetContiner::spacing() const
{
	return widgetsSpacing;
}
