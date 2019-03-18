/**
 * File name: RkBoxLayoutImpl.h
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

#ifndef RK_BOX_LAYOUT_IMPL_H
#define RK_BOX_LAYOUT_IMPL_H

#include "RkBoxLayout.h"
#include "RkLayoutImpl.h"

#include <vector>

class RkBoxLayoutWidgetElement: public RkLayoutElement {
 public:
        RkBoxLayoutWidgetElement(RkWidget* widget);
        ~RkBoxLayoutWidgetElement();
        Type type() const final;
        int minimumWidth() const final;
        int maximumWidth() const final;
        int minimumHeight() const final;
        int maximumHeight() const final;
        int width() const final;
        int hight() const final;
        void setWidth(int width) final;
        void setHeight(int height) final;
        bool fixedWidth() const final;
        bool fixedHeight() const final;
        void setSize(const std::pair<int, int> &size) final;
        RkWidget* widget();

 private:
        RkWidget* elementWidget;
};


class RkBoxLayout::RkBoxLayoutImpl: public RkLayout::RkLayoutImpl {
 public:
        explicit RkBoxLayoutImpl(RkBoxLayout* interface,
                                 RkWidget* parent = nullptr,
                                 Orientation orientation = Orientation::Horizontal);
        ~RkBoxLayoutImpl();
        std::vector<RkBoxLayoutWidgetElement*> stretchables() const;
        void addWidget(RkWidget *widget);
        void setOrientation(Orientation orientation);
        Orientation orientation();
        void update() final;

 protected:
        std::vector<RkBoxLayoutWidgetElement*> strachables() const;
        int getMinimum();
        void setAllToMinmum();
        void arrangeItems();
        int boxLength();

 private:
        RK_DISABLE_COPY(RkBoxLayoutImpl)
        RK_DISABLE_MOVE(RkBoxLayoutImpl)
        RK_DECALRE_INTERFACE_PTR(RkBoxLayout)
        Orientation boxOrientation;
};

#endif // RK_BOX_LAYOUT_IMPL_H
