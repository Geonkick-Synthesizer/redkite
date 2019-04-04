/**
 * File name: RkColor.h
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

#ifndef  RK_COLOR_H
#define  RK_COLOR_H

#include "Rk.h"

class RkColor {
 public:

        constexpr RkColor()
                : redValue{255}
                , greenValue{255}
                , blueValue{255}
                , alphaValue{255}
       {
       }

       constexpr RkColor(int red, int green, int blue, int alpha = 255)
               : redValue(red)
               , greenValue(green)
               , blueValue(blue)
               , alphaValue(alpha)
       {
       }

       constexpr bool operator==(const RkColor &other)
       {
               return other.redValue == redValue
               && other.greenValue == greenValue
               && other.blueValue == blueValue
               && other.alphaValue == alphaValue;
       }

       constexpr bool operator!=(const RkColor &other)
       {
               return other.redValue != redValue
               || other.greenValue != greenValue
               || other.blueValue != blueValue
               || other.alphaValue != alphaValue;
       }

       constexpr int red() const
       {
               return redValue;
       }

       constexpr int green() const
       {
               return greenValue;
       }

       constexpr int blue() const
       {
               return blueValue;
       }

       constexpr int alpha() const
       {
               return alphaValue;
       }

       constexpr void setRed(int red)
       {
               redValue = red;
       }

       constexpr void setGreen(int green)
       {
               greenValue = green;
       }

       constexpr void setBlue(int blue)
       {
               blueValue = blue;
       }

       constexpr void setAlpha(int alpha)
       {
               alphaValue = alpha;
       }

 private:
        unsigned short redValue;
        unsigned short greenValue;
        unsigned short blueValue;
        unsigned short alphaValue;
};

#endif // RK_COLOR_H
