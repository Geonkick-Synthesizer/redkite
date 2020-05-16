/**
 * File name: Popup.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://iuriepage.wordpress.com>
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
#include "RkButton.h"

#include <vector>

int main(int arc, char **argv)
{
        RkMain app(arc, argv);

        auto mainWindow = new RkWidget(&app);
        mainWindow->setTitle("Main Window");
        mainWindow->setSize(400, 500);
        mainWindow->setBackgroundColor({50, 100, 50});

        auto button = new RkButton(mainWindow);
        button->setTitle("Button");
        button->setBackgroundColor({255, 0, 0});
        button->setPosition(400, 40);
        button->setSize(10, 10);
        button->show();

        auto mainChild = new RkButton(mainWindow);
        mainChild->setTitle("mainChild");
        mainChild->setBackgroundColor({0, 0, 200});
        mainChild->setPosition(0, 0);
        mainChild->setSize(200, 200);
        mainChild->show();

        RK_ACT_BINDL(button, pressed, RK_ACT_ARGS(), [&]() {
                        auto popup = new RkWidget(mainWindow, Rk::WindowFlags::Popup);
                        popup->setTitle("Popup");
                        popup->setSize(170, 110);
                        popup->setBackgroundColor({80, 80, 80, 50});
                        auto child = new RkWidget(popup);
                        child->setTitle("Child on Popup");
                        child->setPosition(5, 5);
                        child->setBackgroundColor({80, 80, 80});
                        child->setSize(40, 40);
                        child->show();
                        popup->show();
                        popup->setPosition(10, 10);

                });

        mainWindow->show();
        mainWindow->setPosition(120, 120);
        int res = app.exec();
        return res;
}


