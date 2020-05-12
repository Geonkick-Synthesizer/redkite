/**
 * File name: Trainsition.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor <http://geontime.com>
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
#include "RkMain.h"
#include "RkWidget.h"
#include "RkButton.h"
#include "RkTransition.h"

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    auto widget = new RkWidget(&app);
    widget->setTitle("Transition Example");
    widget->setSize(350, 350);
    widget->show();

    auto button = new RkButton(widget);
    button->setCheckable(true);
    button->setSize(48, 48);
    button->setPosition(10, 10);
    button->setBorderWidth(1);
    button->setBorderColor(255, 0, 0);
    button->show();
    RK_ACT_BINDL(button, toggled, RK_ACT_ARGS(bool b),
                 [](bool b){ RK_LOG_INFO("Button: " << b);
                 });

    auto transition = new RkTransition(button);
    transition->setRange(button->width(), button->width() + 100);
    transition->setCallback([button](int value) {
                    button->setSize(value, value);
            });
    transition->start();

    return app.exec();
}
