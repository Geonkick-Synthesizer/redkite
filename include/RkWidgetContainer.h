/**
 * File name: RkWidgetContainer.h
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

#ifndef RK_CONTAINER_H
#define RK_CONTAINER_H

#include "RkWidget.h"

class RK_EXPORT RkWidgetContainer {
  public:
	using RkWidgetContainerSpace = size_t;
        RkWidgetContainer(RkWidget *parent, Rk::Orientation orientation = Rk::Orientation::Horizontal);
        virtual ~RkWidgetContainer() = default;
	void addWidget(RkWidget *widget, Rk::Alignment align = Rk::Alignment::AlignLeft);
	void removeWidget(RkWidget *widget);
	void addSpace(RkWidgetContainerSpace space, Rk::Alignment align = Rk::Alignment::AlignLeft);
	void removeAt(size_t index);
	void update();
	void clear();
	Rk::Orientation orientation() const;
	Rk::Alignment alignment(RkWidget *widget) const;
	Rk::Alignment alignment(size_t index) const;
	void setSize(const RkSize &size);
	RkSize size() const;
	int width() const;
	void setWidth(int width);
	int height() const;
	void setHeight(int height);
	void setPosition(const RkPoint &position);
	RkPoint position() const;
	void setSpacing(size_t space);
	size_t spacing() const;

 protected:
	int initPosition(Rk::Alignment alignment);

 private:
        RK_DISABLE_COPY(RkWidgetContainer);
        RK_DISABLE_MOVE(RkWidgetContainer);
	RkWidget *parentWidget;
	Rk::Orientation containerOrientation;
	int idGenerator;
	std::vector<size_t> itemsIds;
	std::unordered_map<size_t, std::pair<int, RkWidget*>> widgets;
	std::unordered_map<size_t, std::pair<int, RkWidgetContainerSpace>> spaces;
	RkSize containerSize;
	RkPoint containerPosition;
	size_t widgetsSpacing;
};

#endif // RK_CONTAINER_H
