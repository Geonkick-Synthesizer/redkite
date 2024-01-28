/**
 * File name: RkPainter.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor 
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

#include <RkLog.h>

RkPainter::RkPainter(RkCanvas *canvas)
        : o_ptr{std::make_unique<RkPainterImpl>(this, canvas)}
        , impl_ptr{static_cast<RkPainterImpl*>(o_ptr.get())}
{
}

RkPainter::~RkPainter()
{
}

void RkPainter::drawText(int x, int y, const std::string &text)
{
        if (!text.empty())
                impl_ptr->drawText(text, x, y);
}

void RkPainter::drawText(const RkPoint &p,  const std::string &text)
{
        drawText(p.x(), p.y(), text);
}

void RkPainter::drawText(const RkRect &rect,
                         const std::string &text,
                         Rk::Alignment alignment)
{
        if (!text.empty()) {
                RkFont f = font();
                int x;
                if (alignment == Rk::Alignment::AlignLeft)
                        x = rect.left();
                else if (alignment == Rk::Alignment::AlignCenter)
                        x = rect.left() + (rect.width() - impl_ptr->getTextWidth(text)) / 2;
                else
                        x = rect.right() - impl_ptr->getTextWidth(text);
                int y = rect.top() + f.size() + (rect.height() - f.size()) / 2;
                drawText(x, y, text);
        }
}

void RkPainter::drawImage(const RkImage &image, int x, int y)
{
        RK_LOG_DEBUG("called");
        if (!image.isNull())
                impl_ptr->drawImage(image, x, y);
}

void RkPainter::drawCircle(int x, int y, int radius)
{
        if (radius > 0)
                impl_ptr->drawEllipse(RkPoint(x, y), 2 * radius, 2 * radius);
}

void RkPainter::drawCircle(const RkPoint &p, int radius)
{
        if (radius > 0)
                impl_ptr->drawEllipse(p, 2 * radius, 2 * radius);
}

void RkPainter::drawLine(int x1, int y1, int x2, int y2)
{
        if (RkPoint(x1, y1) != RkPoint(x2, y2))
                drawLine(RkPoint(x1, y1), RkPoint(x2, y2));
}

void RkPainter::drawLine(const RkPoint &p1, const RkPoint &p2)
{
        if (p1 != p2)
                impl_ptr->drawLine(p1, p2);
}

void RkPainter::drawRect(const RkRect &rect)
{
        impl_ptr->drawRect(rect);
}

void RkPainter::drawPolyline(const std::vector<RkPoint> &points)
{
        if (points.size() > 1)
                impl_ptr->drawPolyline(points);
}

void RkPainter::fillRect(const RkRect &rect, const RkColor &color)
{
        if (rect.area() > 0)
                impl_ptr->fillRect(rect, color);
}

void RkPainter::applyAlpha(int alpha)
{
        impl_ptr->applyAlpha(alpha);
}

const RkPen& RkPainter::pen() const
{
        return impl_ptr->pen();
}

void RkPainter::setPen(const RkPen &pen)
{
        return impl_ptr->setPen(pen);
}

const RkFont& RkPainter::font() const
{
        return impl_ptr->font();
}

void RkPainter::setFont(const RkFont &font)
{
        impl_ptr->setFont(font);
}

void RkPainter::translate(const RkPoint &offset)
{
        impl_ptr->translate(offset);
}

void RkPainter::rotate(rk_real angle)
{
        impl_ptr->rotate(angle);
}

int RkPainter::getTextWidth(const std::string &text) const
{
        return impl_ptr->getTextWidth(text);
}
