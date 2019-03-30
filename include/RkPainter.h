/**
 * File name: RkPainter.h
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

#ifndef RK_PAINTER_H
#define RK_PAINTER_H

#include "Rk.h"
#include "RkImage.h"

class RkCanvas;

class RkPainter {
 public:
        RkPainter(RkCanvas *canvas);
        ~RkPainter();
        void drawText(const std::string &text, int x, int y);
        void drawImage(const RkImage &image, int x, int y);
        int fontSize() const;

 protected:
        RK_DECLARE_IMPL(RkPainter)

 private:
        RK_DISABLE_COPY(RkPainter)
        RK_DISABLE_MOVE(RkPainter)
};

#endif // RK_PAINTER_H
