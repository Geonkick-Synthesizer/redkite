/**
 * File name: RkContainerWidgetItem.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor <http://iuriepage.wordpress.com>
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

#ifndef RK_CONTAINER_WIDGET_ITEM_H
#define RK_CONTAINER_WIDGET_ITEM_H

#include <RkContainerItem.h>

class RkWidget;

class RK_EXPORT RkContainerWidgetItem: public RkContainerItem {
 public:
       RkContainerWidgetItem(RkWidget *parent,
                            Rk::Alignment align = Rk::Alignment::AlignLeft)
                 : RkContainerItem(parent, ItemType::ItemContainer, align)
                 , itemWidget{parent} {}
        virtual ~RkContainerWidgetItem() = default;
        void setPosition(const RkPoint &point) override { itemWidget->setPosition(point); }
        RkPoint position() const { return itemWidget->position(); }
        void setX(int val) { itemWidget->setX(val); }
        int x() const { return itemWidget->x(); }
        void setY(int val) { itemWidget->setY(val); }
        int y() const { itemWidget->y(); }
        void setSize(const RkSize &size) { itemWidget->setSize(size); }
        RkSize size() const { return itemWidget->size(); }
        void setWidth(int val) { itemWidget->setWidth(val); }
        int width() const { return itemWidget->width(); }
        void setHeight(int val) { itemWidget->setHeight(val); }
        int height() const { itemWidget->height(); }
        RkWidget* widget() const { return itemWidget; }
 private:
        RK_DISABLE_COPY(RkContainerWidgetItem);
        RK_DISABLE_MOVE(RkContainerWidgetItem);
        RkSize itemSize;
        RkWidget *itemWidget;
};

#endif // RK_CONTAINER_WIDGET_ITEM_H
