/**
 * File name: RkLabelImpl.cpp
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

#include "RkLabelImpl.h"

RkLabel::RkLabelImpl::RkLabelImpl(RkLabel *interface, const std::string &text, RkWidget *parent)
    : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
    , inf_ptr{interface}
    , labelText{text}
{
}

RkLabel::RkLabelImpl::~RkLabelImpl()
{
}

void RkLabel::RkLabelImpl::setText(const std::string &text)
{
        labelText = text;
}

std::string RkLabel::RkLabelImpl::text() const
{
        return labelText;
}

void RkLabel::RkLabelImpl::setImage(const RkImage &image)
{
        labelImage = image;
}

void RkLabel::RkLabelImpl::drawLabel()
{
        RkContext painter(inf_ptr);
        if (!labelText.empty()) {
                painter->drawText(labelText, 0, 0);
        } else if (!labelImage.isNull()) {
                int w = image.width() > inf_ptr.width() ? inf_ptr.width() : image.width();
                int h = image.height() > inf_ptr.height() ? inf_ptr.height() : image.height();
                painter->drawImage(image, 0, 0, w, h);
        }
}

