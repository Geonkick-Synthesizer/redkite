/**
 * File name: RkMain.cpp
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
#include "RkLog.h"
#include "RkWidget.h"

RkMain::RkMain() : implMain(std::make_unique<RkMainImpl>())
{
}

RkMain::RkMain(int argc, char **argv) : implMain(std::make_unique<RkMainImpl>(argc, argv))
{
}

RkMain::~RkMain()
{
        if (mainImpl->topLevelWindow())
                delete mainImpl->topLevelWindow();
}

bool RkMain::setTopLevelWindow(RkWidget *widget)
{
        return mainImpl->setTopLevelWindow(widget);
}

int RkMain::exec(bool block)
{
        if (!mainImpl->topLevelWindow()) {
                RK_LOG_ERROR("top level window is not set");
                return 1;
        }

	return mainImpl->exec(block);
}
