/**
 * File name: RkTabImpl.cpp
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

#include "RkTabImpl.h"
#include "RkContainer.h"
#include "RkButton.h"
#include "RkLog.h"

RkTab::RkTabImpl::RkTabImpl(RkTab *interface, RkWidget *parent)
        : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
        , inf_ptr{interface}
{
}

void RkTab::RkTabImpl::addTab(RkWidget *tab, const RkImage &tabButton)
{
        mainContainer->setSize(inf_ptr->size());
        buttonsContainer->setSize({inf_ptr->size().width(), tabButton.height()});
        mainContainer->update();
        auto button = new RkButton(inf_ptr);
        RK_ACT_BINDL(button, pressed, RK_ACT_ARGS(), [=](){
                                                             for (const auto &tab: tabsList) {
                                                                     if (tab.first == button)
                                                                             tab.second->show();
                                                                     else
                                                                             tab.second->hide();
                                                             }
                                                             mainContainer->update();
                                                       });
        button->setImage(tabButton);
        button->show();
        buttonsContainer->addWidget(button);
        tab->setSize(inf_ptr->size());
        if (tabsList.empty())
                tab->show();
        else
                tab->hide();
        mainContainer->addWidget(tab);
        tabsList.push_back({button, tab});
}

RkWidget* RkTab::RkTabImpl::tab(size_t index) const
{
        if (index < tabsList.size())
                return tabsList[index].second;
        return nullptr;
}

void RkTab::RkTabImpl::showTab(size_t index)
{
        if (index < tabsList.size()) {
                size_t i = 0;
                for (const auto &tab: tabsList) {
                        if (i == index) {
                                tab.first->setPressed(true);
                                tab.second->show();
                        } else {
                                tab.first->setPressed(false);
                                tab.second->hide();
                        }                        
                        i++;
                }
                mainContainer->update();
        }
}

void RkTab::RkTabImpl::showTab(RkWidget *tab)
{
        auto res = std::find_if(tabsList.begin(),
                                tabsList.end(),
                                [&] (const auto &t) {
                                        return t.second == tab;
                                });
        if (res == tabsList.end())
                return;
        
        for (const auto &t: tabsList) {
                if (t.second == tab) {
                        t.first->setPressed(true);
                        t.second->show();
                } else {
                        t.first->setPressed(false);
                        t.second->hide();
                }                        
        }
        mainContainer->update();
}

void RkTab::RkTabImpl::initLayout()
{
        mainContainer = new RkContainer(inf_ptr, Rk::Orientation::Vertical);
        buttonsContainer = new RkContainer(inf_ptr);
        mainContainer->addContainer(buttonsContainer, Rk::Alignment::AlignTop);
}
