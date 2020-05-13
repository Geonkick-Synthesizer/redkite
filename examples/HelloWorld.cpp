/**
 * File name: HelloWorld.cpp
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

#include "RkMain.h"
#include "RkWidget.h"

/**
 * This is the simplest use case of Redkite.
 * Create the main window.
 */

int main(int arc, char **argv)
{
    /**
     * Craate the Redkite main object.
     * It creates the main GUI thread loop
     * and handles events and actions.
     */
     RkMain app(arc, argv);

     /**
      * Create a widget. If passing the main object
      * as parent to this widget it will become the main window.
      * All the other created widget must have this
      * widget as parent.
      */
    auto widget = new RkWidget(&app);

    // Set the widget title. This will be seen in the window
    // title bar if is a main window or a dialog with title bar.
    widget->setTitle("Hello World!");

    // Show the widget. By default all widgets are not shown.
    widget->show();

    /**
     * Run the main loop. This will be blocking and
     * will exit until the main window will be closed.
     * By default exec is blocking. But can be called as
     * non-blocking, useful for GUI plugins.
     */
    auto res = app.exec();
    return res;
}


