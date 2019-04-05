/**
 * File name: RkPainterImpl.cpp
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

#include "RkPainterImpl.h"
#include "RkCairoGraphicsBackend.h"
#include "RkLog.h"

RkPainter::RkPainterImpl::RkPainterImpl(RkPainter* interface, RkCanvas* canvas)
        : inf_ptr{interface}
#ifdef RK_GRAPHICS_CAIRO_BACKEND
        , backendGraphics{std::make_unique<RkCairoGraphicsBackend>(canvas)}
#else
#error No graphics backend defined
#endif
{
        backendGraphics->setPen(painterPen);
}

RkPainter::RkPainterImpl::~RkPainterImpl()
{
}

void RkPainter::RkPainterImpl::drawText(const std::string &text, int x, int y)
{
        backendGraphics->drawText(text, x, y);
}

void RkPainter::RkPainterImpl::drawImage(const std::string &file, int x, int y)
{
        backendGraphics->drawImage(file, x, y);
}

void RkPainter::RkPainterImpl::drawImage(const RkImage &image, int x, int y)
{
        backendGraphics->drawImage(image, x, y);
}

void RkPainter::RkPainterImpl::drawEllipse(const RkPoint& p, int width, int height)
{
        backendGraphics->drawEllipse(p, width, height);
}

void RkPainter::RkPainterImpl::drawLine(const RkPoint &p1, const RkPoint &p2)
{
        backendGraphics->drawLine(p1, p2);
}

void RkPainter::RkPainterImpl::drawPolyline(const std::vector<RkPoint> &points)
{
        backendGraphics->drawPolyLine(points);
}

const RkPen& RkPainter::RkPainterImpl::pen() const
{
        return painterPen;
}

void RkPainter::RkPainterImpl::setPen(const RkPen &pen)
{
        backendGraphics->setPen(pen);
        painterPen = pen;
}

int RkPainter::RkPainterImpl::fontSize() const
{
        return backendGraphics->getFontSize();
}

