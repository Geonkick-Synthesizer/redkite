/**
 * File name: RkMain.h
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

#ifndef RK_MAIN_H
#define RK_MAIN_H

#include "Rk.h"

class RkWidget;

class RkMain {
  public:
          RkMain();
          RkMain(int argc, char **argv);
          ~RkMain();
          RkMain(const RkMain &other) = delete;
          RkMain& operator=(const RkMain &other) = delete;
          RkMain(RkMain &&other) = delete;
          RkMain& operator=(RkMain &&other) = delete;
          bool setTopLevelWindow(RkWidget* widget);
          int exec();
  private:

/**
 * Private implementations for platforms.
 * Not to be exposed to users.
 * This also provides ABI compatibility.
 */
#ifdef RK_OS_WIN
	  RK_PRIVATE_IMPL(RkMainWin, privateMain);
#elif RK_OS_MAC
	  RK_PRIVATE_IMPL(RkMainMac, privateMain);
#else
	  RK_PRIVATE_IMPL(RkMainXWin, privateMain);
#endif
};

#endif // RK_MAIN_H
