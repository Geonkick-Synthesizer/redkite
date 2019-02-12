/**
 * File name: RkMainImpl.cpp
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

#include "RkLog.h"
#include "RkWidget.h"
#include "RkMainImpl.h"

#ifdef RK_WIN_OS
#include "RkEventQueueWin.h"
#elif RK_MAC_OS
#include "RkEventQueueMac.h"
#else
#include "RkEventQueueX.h"
#endif

RkMain::RkMainImpl::RkMainImpl(RkMain *interface)
        : inf_ptr{interface}
        , topWindow(nullptr)
        , eventQueue{nullptr}
{
        RK_LOG_INFO("called");
}

RkMain::RkMainImpl::RkMainImpl(RkMain *interface, int argc, char **argv)
        : inf_ptr{interface}
        , platformMain{nullptr}
        , topWindow(nullptr)

{
        RK_UNUSED(argc);
        RK_UNUSED(argv);
        RK_LOG_INFO("called");
}

RkMain::RkMainImpl::~RkMainImpl()
{
        if (topWindow)
                delete topWindow;
}

bool RkMain::RkMainImpl::setTopLevelWindow(RkWidget* widget)
{
      if (topWindow || !widget)
              return false;

      topWindow = widget;
#ifdef RK_WIN_OS
#elif RK_MAC_OS
#else
      eventQueue = std::make_unique<RkEventQueueX>(topWindow->display());
#endif // RK_WIN_OS
      return true;
}

RkWidget* RkMain::RkMainImpl::topLevelWindow(void)
{
      return topWindow;
}

void RkMain::RkMainImpl::processEvents()
{
        while (eventQueue->pending()) {
                auto res = eventQueue.nextEvent();
                if (!res.second)
                        continue;

                RkWidget *widget;
                if (res->first == topLevelWindow()->id())
                        widget = topLevelWindow();
                else
                        widget = topLevelWindow()->child(res->first);

                if (widget)
                        topLevelWindow()->processEvent(res.second);
        }

}

int RkMain::RkMainImpl::exec(bool block)
{
        if (!topLevelWindow()) {
                RK_LOG_ERROR("top window not defined");
		return 1;
	}

        if (!block) {
                processEvents();
        } else {
                for (; block ;) {
                        processEvents();
                        if (topLevelWindow()->isClose())
                                break;
                        std::this_thread::sleep_for(std::chrono::milliseconds(15));
                }
        }

        return 0;
}
