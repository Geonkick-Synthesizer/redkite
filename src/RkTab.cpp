/**
 * File name: RkTab.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2022 Iurie Nistor
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

#include "RkTab.h"
#include "RkTabImpl.h"

RkTab::RkTab(RkWidget *parent)
        : RkWidget(parent, std::make_unique<RkTab::RkTabImpl>(this, parent))
        , impl_ptr{static_cast<RkTab::RkTabImpl*>(o_ptr.get())}
{
        impl_ptr->initLayout();
        show();
}

void RkTab::addTab(RkWidget *tab, const RkImage &tabButton)
{
        impl_ptr->addTab(tab, tabButton);
}

RkWidget* RkTab::tab(size_t index) const
{
        return impl_ptr->tab(index);
}

void RkTab::showTab(size_t index)
{
        impl_ptr->showTab(index);
}

void RkTab::showTab(RkWidget *tab)
{
        impl_ptr->showTab(tab);
}
