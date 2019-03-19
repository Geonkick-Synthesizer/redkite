/**
 * File name: RkLayoutImpl.h
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

#ifndef RK_LAYOUT_IMPL_H
#define RK_LAYOUT_IMPL_H

#include "RkLayout.h"

class RkLayoutElement {
 public:
        enum class Type : int {
                Unknown,
                BoxWidget,
                BoxSpace,
                BoxLayout,
                GridWidget,
                GridLayout,
        };

        enum  Alignment : int {
                Unalingned,
                AlignLeft,
                AlignRight
        };

        RkLayoutElement();
        virtual ~RkLayoutElement();
        virtual Type type() const = 0;
        Alignment alignment() const;
        void setAlignemnt(Alignment alignment);
        virtual int minimumWidth() const = 0;
        virtual int minimumHeight() const = 0;
        virtual int maximumWidth() const = 0;
        virtual int maximumHeight() const = 0;
        virtual void setSize(const std::pair<int, int> &size) = 0;
        virtual void setX(int val) = 0;
        virtual void setY(int val) = 0;
        virtual int x() const = 0;
        virtual int y() const = 0;
        virtual void setHeight(int height) = 0;
        virtual void setWidth(int width) = 0;
        virtual int width() const = 0;
        virtual int height() const = 0;
        virtual bool fixedWidth() const = 0;
        virtual bool fixedHeight() const = 0;
        bool stretchable() const;
        void setStretchable(bool stretchable);

 private:
        Type elementType;
        Alignment elementAlignment;
        bool isStretchable;
};

class RkLayout::RkLayoutImpl {
 public:
        explicit RkLayoutImpl(RkLayout* interface, RkWidget* parent = nullptr);
        virtual ~RkLayoutImpl();
        void addElement(RkLayoutElement* element);
        bool elementExists(const RkLayoutElement* element) const;
        void setPadding(int padding);
        int padding();
        RkWidget* getParentWidget() const;
        const std::list<RkLayoutElement*>& getLayoutElements() const;
        virtual void update();

 private:
        RK_DISABLE_COPY(RkLayoutImpl)
        RK_DISABLE_MOVE(RkLayoutImpl)
        RK_DECALRE_INTERFACE_PTR(RkLayout)
        RkWidget *parentWidget;
        std::list<RkLayoutElement*> layoutElements;
        int elementsPadding;
};

#endif // RK_LAYOUT_IMPL_H
