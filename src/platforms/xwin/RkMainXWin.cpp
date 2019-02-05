/**
 * File name: RkMainXwin.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor (http://quamplex.com/redkite)
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

#include "RkMainXWin.h"

RkMain::RkMainWin::RkMainXWin()
{

}

RkMain::RkMainWin::~RkMainXWin()
{
}

void RkMain::setTopLevelWindow(RkWidget* widget)
{
      topLevelWindow = widget;
}

RkWidget* RkMain::topLevelWindow(void)
{
      return topLevelWindow;
}

int RkMain::RkMainWin::exec()
{
        if (!topLevelWindow) {
                RK_LOG_ERROR("top window not defined");
		return 1;
	}

        for (; !isQuit(); )
	        topLevelWindow->processEvents();
        return exitStatus();
}
