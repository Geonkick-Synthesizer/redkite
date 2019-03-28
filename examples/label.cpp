/**
 * File name: label.cpp
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

#include "RkMain.h"
#include "RkLabel.h"
#include "RkLog.h"

const unsigned char imageRc[] = {};

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    // Create main window.
    auto widget = new RkWidget;
    widget->setTitle("Label Example");
    widget->setSize(250, 250);

    auto label = new RkLabel(widget);
    label->setTitle("Label as child");
    label->setText("Hello!!");
    label->setImage(RkImage(imageRc));
    label->setX(10);
    label->setY(10);
    label->setSize(100, 94);
    label->setBackgroundColor(200, 200, 200);
    label->show();

    if (!app.setTopLevelWindow(widget)) {
            RK_LOG_ERROR("can't set top level window");
            exit(1);
    }

    widget->show();

    RK_LOG_DEBUG("text: " << label->text());

    int res = app.exec();
    return res;
}

