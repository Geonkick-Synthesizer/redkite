/**
 * File name: RkTabImpl.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://geontime.com>
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

#ifndef RK_TAB_IMPL_H
#define RK_TAB_IMPL_H

#include "RkWidgetImpl.h"
#include "RkTab.h"
#include "RkImage.h"

class RkContainer;
class RkButton;

class RkTab::RkTabImpl : public RkWidget::RkWidgetImpl {
 public:
        RkTabImpl(RkTab *interface, RkWidget *parent);
        virtual ~RkTabImpl() = default;
        void initLayout();
        void addTab(RkWidget *tab, const RkImage &tabButton);
        RkWidget* tab(size_t index) const;
        void showTab(size_t index);
        void showTab(RkWidget *tab);
        
 private:
        RK_DECALRE_INTERFACE_PTR(RkTab);
        RkContainer *mainContainer;
        RkContainer *buttonsContainer;
        std::vector<std::pair<RkButton*, RkWidget*>> tabsList;
};

#endif // RK_TAB_IMPL_H
