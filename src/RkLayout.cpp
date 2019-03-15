/**
 * File name: RkLayout.cpp
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

#include "RkLog.h"
#include "RkLayout.h"
#include "RkLayoutImpl.h"

RkLayout::RkLayout(RkWidget *parent)
    : o_ptr{std::make_shared<RkLayoutImpl>(this, parent)}
{
        if (parent)
                parent->setLayout(this);
}

RkLayout::RkLayout(RkWidget *parent, const std::shared_ptr<RkLayoutImpl> &impl)
        : o_ptr{impl}
{
        if (parent)
                parent->setLayout(this);

}

RkLayout::~RkLayout()
{
}

void RkLayout::setPadding(int padding)
{
        o_ptr->setPadding(padding);
        o_ptr->update();
}

int RkLayout::padding() const
{
        return o_ptr->padding();
}


