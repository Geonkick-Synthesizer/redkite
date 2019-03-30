/**
 * File name: RkImageImpl.cpp
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

#include "RkImageImpl.h"
#ifdef RK_GRAPHICS_CAIRO_BACKEND
#include "RkCairoImageBackendCanvas.h"
#else
#error No graphics backend defined.
#endif

RkImage::RkImageImpl::RkImageImpl(RkImage *interface,
                                  const unsigned char *data,
                                  int width,
                                  int height,
                                  RkImage::Format format)
        : inf_ptr{interface}
        , imageFormat{format}
#ifdef RK_GRAPHICS_CAIRO_BACKEND
        , imageBackendCanvas{std::make_unique<RkCairoImageBackendCanvas>(std::make_pair(width, height), imageFormat, data)}
#else
#error No graphics backend defined
#endif
{
}

RkImage::RkImageImpl::~RkImageImpl()
{
}

std::shared_ptr<RkCanvasInfo> RkImage::RkImageImpl::getCanvasInfo() const
{
        return imageBackendCanvas->getCanvasInfo();
}

const unsigned char* RkImage::RkImageImpl::data() const
{
        return imageBackendCanvas->data();
}

std::vector<unsigned char> RkImage::RkImageImpl::dataCopy() const
{
        return imageBackendCanvas->dataCopy();
}

RkImage::Format RkImage::RkImageImpl::format() const
{
        return imageFormat;
}

int RkImage::RkImageImpl::width() const
{
        return imageBackendCanvas->size().first;
}

int RkImage::RkImageImpl::height() const
{
        return imageBackendCanvas->size().second;
}

bool RkImage::RkImageImpl::isNull() const
{
        return !imageBackendCanvas || imageBackendCanvas->isNull();
}

void RkImage::RkImageImpl::createImage(std::pair<int, int> size,
                                       RkImage::Format format,
                                       const unsigned char *data)
{
        imageFormat = format;
#ifdef RK_GRAPHICS_CAIRO_BACKEND
        if (imageBackendCanvas)
                imageBackendCanvas = std::make_unique<RkCairoImageBackendCanvas>(size, format, data);
#else
#error No graphics backend defined
#endif
}
