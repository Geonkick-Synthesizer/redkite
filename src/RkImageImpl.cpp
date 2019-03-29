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
#include "RkImageBackendCanvas.h"
#else
#error No graphics backend defined.
#endif

RkImage::RkImageImpl::RkImageImpl(RkImage *interface, const std::string &file)
        : inf_ptr{interface}
        , imageFormat{RkImage::Format::ARGB32}
#ifdef RK_GRAPHICS_CAIRO_BACKEND
        , imageBackendCanvas{std::make_unique<RkCairoImageBackendCanvas>(imageSize, imageFormat)}
#else
#error No graphics backend defined
#endif
{
}

RkImage::RkImageImpl::RkImageImpl(RkImage *interface,
                                  const unsigned char *data,
                                  int width,
                                  int height,
                                  Format format = Format::ARGB32)
        : inf_ptr{interface}
        , imageFormat{format}
#ifdef #ifdef RK_GRAPHICS_CAIRO_BACKEND
        , imageBackendCanvas{std::make_sared<RkCairoImageBackendCanvas>({width, height}, imageFormat)}
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

std::unique_ptr<unsigned char*> RkImage::RkImageImpl::dataCopy() const
{
        return imageBackendCanvas->dataCopy()
}

RkImage::Format RkImage::RkImageImpl::format() const
{
        return imageFormat;
}
        
int RkImage::RkImageImpl::width() const
{
        return imageBackendCanvas->size().first;
}

int RkImage::RkImageImpl::height() cons
{
        return imageBackendCanvas.size().second;
}

bool RkImage::RkImageImpl::isNull() const
{
        return imageBackendCanvas.isNull();
}
