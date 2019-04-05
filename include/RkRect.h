/**
 * File name: RkRect.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://quamplex.com>
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

#ifndef  RK_RECT_H
#define  RK_RECT_H

#include "RkSize.h"
#include "RkPoint.h"

class RkRect {
 public:

        constexpr RkRect()
                : rectTopLeft(0, 0)
                , rectSize(0, 0)
        {
        }

        constexpr RkRect(int x, int y, int width, int height)
                : rectTopLeft(x, y)
                , rectSize(width, height)
        {
        }

        constexpr RkRect(const RkPoint &topLeft, const RkSize &size)
                : rectTopLeft{topLeft}
                , rectSize{size}

        {
        }

        constexpr RkRect(const RkPoint &topLeft, const RkPoint &bottomRight)
                : rectTopLeft{topLeft}
                , rectSize(std::abs(bottomRight.x() - topLeft.x()), std::abs(bottomRight.y() - topLeft.y()))
        {
        }

        friend constexpr bool operator==(const RkRect &r1, const RkRect &r2)
        {
               return r1.rectSize == r2.rectSize && r1.rectTopLeft == r2.rectTopLeft;
        }

        friend constexpr bool operator!=(const RkRect &r1, const RkRect &r2)
        {
                return r1.rectSize != r2.rectSize || r1.rectTopLeft != r2.rectTopLeft;
        }

        constexpr int width() const
        {
                return rectSize.width();
        }

        constexpr void setWidth(int width)
        {
                rectSize.setWidth(width);
        }

        constexpr int height() const
        {
                return rectSize.height();
        }

        constexpr void setHeight(int height)
        {
                rectSize.setHeight(height);
        }

        constexpr RkSize size() const
        {
                return rectSize;
        }

        constexpr void setSize(const RkSize &size)
        {
                rectSize = size;
        }

        constexpr void setTopLeft(const RkPoint &p)
        {
                rectTopLeft = p;
        }

        constexpr void setTopRight(const RkPoint &p)
        {
                rectTopLeft = p;
        }

        constexpr void setBottomLeft(const RkPoint &p)
        {
                rectTopLeft = p;
        }

        constexpr void setBottomRight(const RkPoint &p)
        {
                rectTopLeft = p;
        }

        constexpr RkPoint topLeft() const
        {
                return rectTopLeft;
        }

        constexpr RkPoint topRight() const
        {
                return rectTopLeft;
        }

        constexpr RkPoint bottomLeft() const
        {
                return rectTopLeft;
        }

        constexpr RkPoint bottomRight(void) const
        {
                return rectTopLeft;
        }

        constexpr int left() const
        {
                return rectTopLeft.x();
        }

        constexpr int top() const
        {
                return rectTopLeft.y();
        }

        constexpr int bottom() const
        {
                return rectTopLeft.y() + rectSize.height();
        }

        constexpr int right() const
        {
                return rectTopLeft.x() + rectSize.width();
        }

 private:
       RkPoint rectTopLeft;
       RkSize  rectSize;
};

#endif // RK_RECT_H
