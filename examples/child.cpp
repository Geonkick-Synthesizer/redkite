/**
 * File name: child.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor
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

#include "RkMain.h"
#include "RkWidget.h"
#include "RkLog.h"

#include <vector>

static void setRandomColor(RkWidget* widget)
{
        int red = rand() % 151 + 50;     
        int green = rand() % 151 + 50;
        int blue = rand() % 151 + 50;

        widget->setBorderColor(red, green, blue);
        widget->setBackgroundColor(red, green, blue);
}

static void drawChildren(RkWidget* parent, int l)
{
        if (l > 1)
                return;
        auto wCh = parent->width() / 10;
        auto hCh = parent->height() / 10;
        std::cout << "parent->width(): " << parent->width() << std::endl;
        std::cout << "wCh: " << wCh << std::endl;
        size_t n = 0;
        for (int y = 0; y < parent->height(); y += hCh + 5) {
                for (int x = 0; x < parent->width(); x += wCh + 5) {
                        std::cout << "x: " << x << std::endl;
                        std::cout << "n: " << n++ << std::endl;
                        auto child = new RkWidget(parent);
                        setRandomColor(child);
                        child->setTitle("Child[" + std::to_string(x) + std::to_string(y) + "] - " + std::to_string(l));
                        child->setSize(wCh, hCh);
                        child->setPosition(x, y);
                        child->show();
                        drawChildren(child, l + 1);
                }
        }
}

int main(int arc, char **argv)
{
        RkMain app(arc, argv);

        // Create main window.
        auto mainWindow = new RkWidget(app);
        mainWindow->setTitle("Main Window");
        mainWindow->setSize(800, 600);
        //        mainWindow->setBackgroundColor(80, 150, 80);
        drawChildren(mainWindow, 1);

        /*        int x = 10;
        int y = 10;
        RK_LOG_DEBUG("create childs");
        for (auto i = 0; i < 10; i++) {
                for (auto j = j < )
                RK_LOG_DEBUG("create child " << i);
                auto child = new RkWidget(mainWindow);
                child->setTitle("Child[" + std::to_string(i) + "] - LEVEL 1");
                child->setSize(60, 60);
                child->setPosition(x, y);
                child->setBorderColor(0, 255, 0);
                child->setBackgroundColor(0, 0, 255);
                child->show();

                auto child_l = new RkWidget(child);
                child_l->setTitle("Child[" + std::to_string(i) + "] - LEVEL 2");
                child_l->setPosition(10, 10);
                child_l->setSize(30, 30);
                child_l->setBorderColor(0, 0, 255);
                child_l->setBackgroundColor(255, 0, 0);
                child_l->show();

                x += 65;
                if (x > 650) {
                        y += 65;
                        x = 10;
                }
                }*/

        mainWindow->show();
        int res = app.exec();
        return res;
}
