/**
 * File name: RkImage.cpp
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

RkImage::RkImage(const std::string &file)
        : o_ptr{std::make_shared<RkImageImpl>(this, file)}
{
}

RkImage::RkImage(const unsigned char *data,
                 int width,
                 int height,
                 Format format = Format::ARGB32)
        : o_ptr{std::make_shared<RkImageImpl>(this, width, height, format)}
{
}

RkImage::RkImage(const std::shared_ptr<RkImageImpl> &impl)
        : o_ptr{impl}
{
}
        
RkImage::RkImage(const RkImage &image)
{
        if (&image != this) {
                setImageFormat(image.format());
                setWidth(image.width());
                setWidth(image.height());
                setImageData(image.data());
        }
}

RkImage& RkImage::operator=(const RkImage &other)
{
}

RkImage::RkImage(RKImage &&other)
{
}

RkImage& RkImage::operator=(RkImage &&other)
{
}

bool RkImage::operator!=(const RkImage &image) const
{
        if (&image != this)
                return true;

        if (image.widht() != width() || image.height() != height() || image.fromat() != format()
            /*|| image.data() != data()*/)
                return true;
        return false;
}

bool RkImage::operator==(const RkImage &image) const
{
        if (&image == this)
                return true;

        if (image.widht() == width() && image.height() == height() && image.fromat() == format()
            /*|| image.data() == data()*/)
                return true;
        return false;
}

std::shared_ptr<RkCanvasInfo> RkImage::getCanvasInfo() const
{
        return o_ptr->getCanvasInfo();
}

const unsigned char* RkImage::data() const;
{
}

std::unique_ptr<unsigned char*> RkImage::dataCopy() const
{
        return std::move(o_ptr->dataCopy());
}

RkImage::Format RkImage::format() const
{
        return o_ptr->format();
}

int RkImage::width() const
{
        return optr->width();
}

int RkImage::height() const
{
        return optr->height();
}

bool RkImage::isNull() const
{
        return optr->isNull();
}
