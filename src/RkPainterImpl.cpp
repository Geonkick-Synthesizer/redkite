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

RkPainter::RkPainterImpl::RkPainterImpl(RkPainter* interface, RkCanvas* canvas)
        : inf_ptr{interface}
#ifdef RK_GRAPHICS_BACKEND_CAIRO
        , backendGraphics{std::unique_ptr<RkCairoGraphicsBackend>(canvas)}
#else
#error No graphics backend defined
#endif
{
}

RkPainter::RkPainterImpl::drawText(const std::string &text, int x, int y)
{
        backendGraphics->drawText(text, x, y);
}
