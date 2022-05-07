/**
 * File name: RkTab.h
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

#ifndef RK_TAB_H
#define RK_TAB_H

#include "RkWidget.h"
#include "RkImage.h"

class RK_EXPORT RkTab : public RkWidget {
 public:
        RkTab(RkWidget *parent);
        virtual ~RkTab() = default;
        void addTab(RkWidget *tab, const RkImage &tabButton);
        RkWidget* tab(size_t index) const;
        void showTab(size_t index);
        void showTab(RkWidget *tab);
        RK_DECL_ACT(tabChanged,
                    tabChanged(RkWidget* tab),
                    RK_ARG_TYPE(RkWidget *),
                    RK_ARG_VAL(tab));
 private:
        RK_DISABLE_COPY(RkTab);
        RK_DISABLE_MOVE(RkTab);
        RK_DELCATE_IMPL_PTR(RkTab);
};

#endif // RK_TAB_H
