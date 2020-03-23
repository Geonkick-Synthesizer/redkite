/**
 * File name: RkWidgetContiner.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor <http://geontiem.com>
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

#ifndef RK_CONTINER_H
#define RK_CONTINER_H

#include "RkWidget.h"

class RK_EXPORT RkWidgetContiner {
  public:
	using RkWidgetContinerSpace = size_t;
        RkWidgetContiner(RkWidget *parent, Rk::Orientation orientation = Rk::Orientation::Horizontal);
        virtual ~RkWidgetContiner() = default;
        RK_DISABLE_COPY(RkWidgetContiner)
        RK_DISABLE_MOVE(RkWidgetContiner)
	void addWidget(RkWidget *widget, Rk::Alignment align = Rk::Alignment::AlignLeft);
	void removeWidget(RkWidget *widget);
	void addSpace(RkWidgetContinerSpace space, Rk::Alignment align = Rk::Alignment::AlignLeft);
	void removeAt(size_t index);
	void update();
	void clear();
	Rk::Orientation orientation() const;
	Rk::Alignment alignment(RkWidget *widget) const;
	Rk::Alignment alignment(size_t index) const;
	void setSize(const RkSize &size);
	RkSize size() const;
	void setPosition(const RkPoint &position);
	RkPoint position() const;
	void setSpacing(size_t space);
	size_t spacing() const;

 protected:
	int initPosition(Rk::Alignment alignment);

 private:
	RkWidget *parentWidget;
	Rk::Orientation continerOrientation;
	int idGenerator;
	std::vector<size_t> itemsIds;
	std::unordered_map<size_t, std::pair<int, RkWidget*>> widgets;
	std::unordered_map<size_t, std::pair<int, RkWidgetContinerSpace>> spaces;
	RkSize continerSize;
	RkPoint continerPosition;
	size_t widgetsSpacing;
};

#endif // RK_CONTINER_H
