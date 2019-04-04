/**
 * File name: RkPen.h
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

#ifndef  RK_PEN_H
#define  RK_PEN_H

#include "Rk.h"
#include "RkColor.h"

class RkPen {
 public:

        enum class PenStyle {
                NoLine    = 0,
                SolidLine = 1,
                DashLine  = 2,
                DotLine   = 3
        };

        explicit constexpr RkPen(PenStyle style = PenStyle::SolidLine)
                : penStyleVal{style}
                , penWidthVal{1}
                , penColorVal{RkColor()}
       {
       }

       constexpr RkPen(const RkColor &color)
               :  penStyleVal{PenStyle::SolidLine}
                , penWidthVal{1}
                , penColorVal{color}
       {
       }

       constexpr bool operator==(const RkPen &other)
       {
               return other.penStyleVal == penStyleVal
                      && penColorVal == other.penColorVal
                      && other.penWidthVal == penWidthVal;
       }

       constexpr bool operator!=(const RkPen &other)
       {
               return other.penStyleVal != penStyleVal
                      || penColorVal != other.penColorVal
                      || other.penWidthVal != penWidthVal;
       }

       constexpr PenStyle style() const
       {
               return penStyleVal;
       }

       constexpr void setPenStyle(PenStyle style)
       {
               penStyleVal = style;
       }

       constexpr RkColor color() const
       {
               return penColorVal;
       }

       constexpr void setPenColor(const RkColor &color)
       {
               penColorVal = color;
       }

 private:
       PenStyle penStyleVal;
       int penWidthVal;
       RkColor penColorVal;
};

#endif // RK_PEN_H
