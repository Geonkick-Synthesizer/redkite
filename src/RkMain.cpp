/**
 * File name: RkMain.cpp
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

#include "RkMain.h"
#include "RkLog.h"
#include "RkWidget.h"

#ifdef RK_WIN_OS
#include "RkMainWin.h"
#elif RK_MAC_OS
#include "RkMainMac.h"
#else
#include "RkMainXWin.h"
#endif

RkMain::RkMain()
#ifdef RK_WIN_OS
  : privateMain(std::make_unique<RkMainWin>())
#elif RK_MAC_OS
  : privateMain(std::make_unique<RkMainMac>())
#else
  : privateMain(std::make_unique<RkMainXWin>())
#endif
{
       RK_LOG_INFO("called");
}

RkMain::RkMain(int argc, char **argv)
 #ifdef RK_WIN_OS
  : privateMain(std::make_unique<RkMainWin>())
#elif RK_MAC_OS
  : privateMain(std::make_unique<RkMainMac>())
#else
  : privateMain(std::make_unique<RkMainXWin>())
#endif
{
       RK_UNUSED(argc);
       RK_UNUSED(argv);
       RK_LOG_INFO("called");
}

RkMain::~RkMain()
{
}

bool RkMain::setTopLevelWindow(RkWidget *widget)
{
        if (privateMain->topLevelWindow()) {
                RK_LOG_ERROR("top level window is already set");
		return false;
        }	
        return privateMain->setTopLevelWindow(widget);
}

int RkMain::exec()
{
        if (!privateMain->topLevelWindow()) {
                RK_LOG_ERROR("top level window is not set");
                return 1;
        }

	return privateMain->exec();
}
