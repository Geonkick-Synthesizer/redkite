/**
 * File name: RkCairoGraphicsBackend.cpp
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

#include "RkCairoGraphicsBackend.h"
#include "RkCanvas.h"
#include "RkCanvasInfo.h"
#include "RkLog.h"

RkCairoGraphicsBackend::RkCairoGraphicsBackend(RkCanvas *canvas)
        : cairoContext{cairo_create(canvas->getCanvasInfo()->cairo_surface)}
        , fontSize{12}
{
        cairo_set_font_size(cairoContext, getFontSize());
}

RkCairoGraphicsBackend::~RkCairoGraphicsBackend()
{
        cairo_destroy(cairoContext);
}

void RkCairoGraphicsBackend::drawText(const std::string &text, int x, int y)
{
        cairo_move_to(cairoContext, x, y);
        cairo_show_text(cairoContext, text.c_str());
}

void RkCairoGraphicsBackend::drawImage(const std::string &file, int x, int y)
{
        auto image = cairo_image_surface_create_from_png(file.c_str());
        cairo_set_source_surface(cairoContext, image, x, y);
        cairo_paint(cairoContext);
        cairo_surface_destroy(image);
}

void RkCairoGraphicsBackend::drawImage(const RkImage &image, int x, int y)
{
        auto stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, image.width());
        auto image_data = image.dataCopy();
        auto img = cairo_image_surface_create_for_data(image_data.data(),
                                                       CAIRO_FORMAT_ARGB32,
                                                       image.width(),
                                                       image.height(),
                                                       stride);
        cairo_set_source_surface(cairoContext, img, x, y);
        cairo_paint(cairoContext);
        cairo_surface_destroy(img);
}

int RkCairoGraphicsBackend::getFontSize() const
{
        return fontSize;
}

void RkCairoGraphicsBackend::setFontSize(int size)
{
        fontSize = size;
}

