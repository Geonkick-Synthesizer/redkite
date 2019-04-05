/**
 * File name: RkPainter.cpp
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

#include "RkPainter.h"
#include "RkPainterImpl.h"

RkPainter::RkPainter(RkCanvas *canvas)
        : o_ptr{std::make_shared<RkPainterImpl>(this, canvas)}
{
}

RkPainter::~RkPainter()
{
}

void RkPainter::drawText(const std::string &text, int x, int y)
{
        o_ptr->drawText(text, x, y);
}

void RkPainter::drawImage(const RkImage &image, int x, int y)
{
        o_ptr->drawImage(image, x, y);
}

void RkPainter::drawCircle(int x, int y, int radius)
{
        o_ptr->drawEllipse(RkPoint(x, y), 2 * radius, 2 * radius);
}

void RkPainter::drawCircle(const RkPoint &p, int radius)
{
        o_ptr->drawEllipse(p, 2 * radius, 2 * radius);
}

void RkPainter::drawLine(int x1, int y1, int x2, int y2)
{
        drawLine(RkPoint(x1, y1), RkPoint(x2, y2));
}

void RkPainter::drawLine(const RkPoint &p1, const RkPoint &p2)
{
        o_ptr->drawLine(p1, p2);
}

void RkPainter::drawPolyline(const std::vector<RkPoint> &points)
{
        if (!points.empty())
                o_ptr->drawPolyline(points);
}

const RkPen& RkPainter::pen() const
{
        return o_ptr->pen();
}

void RkPainter::setPen(const RkPen &pen)
{
        return o_ptr->setPen(pen);
}

int RkPainter::fontSize() const
{
        return o_ptr->fontSize();
}
