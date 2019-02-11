/**
 * File name: RkLabel.cpp
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

#include "RkLabel.h"
#include "RkLabelImpl.h"

RkLabel::RkLabel(RkWidget *parent)
        : RkWidget(parent, std::static_pointer_cast<RkWidget::RkWidgetImpl>(std::make_shared<RkLabel::RkLabelImpl>(this, std::string(), parent)))
        , impl_ptr{std::static_pointer_cast<RkLabel::RkLabelImpl>(o_ptr)}
{
}

RkLabel::RkLabel(const std::string &text, RkWidget *parent)
        : RkWidget(parent, std::static_pointer_cast<RkLabel::RkWidgetImpl>(std::make_shared<RkLabel::RkLabelImpl>(this, text, parent)))
        , impl_ptr{std::static_pointer_cast<RkLabel::RkLabelImpl>(o_ptr)}
{
}


//RkLabel::RkLabel(RkLabelImpl &impl)
//    : RkWidget(impl)
//    , impl_ptr{static_cast<RkLabelImpl*>(o_ptr)}
//{
//}

void RkLabel::setText(const std::string &text)
{
     impl_ptr->setText(text);
}

std::string RkLabel::text() const
{
     return impl_ptr->text();
}
