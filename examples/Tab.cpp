/**
 * File name: WidgetTabs.cpp
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

#include <RkMain.h>
#include <RkWidget.h>
#include <RkImage.h>
#include "RkTab.h"

int main(int arc, char **argv)
{
        RkMain app(arc, argv);

        // Create main window.
        auto mainWindow = new RkWidget(&app);
        mainWindow->setTitle("Widget Tabs");
        mainWindow->setSize(500, 400);
        mainWindow->show();

        // Create the tabs widget.
        auto widgetTabs = new RkTab(mainWindow);
        widgetTabs->setBackgroundColor(23, 45, 66);
        widgetTabs->setFixedSize(300, 300);
        widgetTabs->setPosition(30, 30);

        // Create and add tabs.
        RkImage tabButton(64, 24);
        auto tab = new RkWidget(widgetTabs);
        tab->setBackgroundColor({255, 0, 0});
        tabButton.fill({255, 0, 0});
        widgetTabs->addTab(tab, tabButton);

        tab = new RkWidget(widgetTabs);
        tab->setBackgroundColor({0, 255, 0});
        tabButton.fill({0, 255, 0});
        widgetTabs->addTab(tab, tabButton);

        tab = new RkWidget(widgetTabs);
        tab->setBackgroundColor({0, 0, 255});
        tabButton.fill({0, 0, 255});
        widgetTabs->addTab(tab, tabButton);
        widgetTabs->showTab(1);

        return app.exec();
}

