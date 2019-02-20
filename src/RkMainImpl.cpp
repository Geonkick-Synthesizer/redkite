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
#include "RkPlatform.h"

#ifdef RK_OS_WIN
#include "RkEventQueueWin.h"
#elif RK_OS_MAC
#include "RkEventQueueMac.h"
#else
#include "RkEventQueueX.h"
#endif

#include <chrono>
#include <thread>

RkMain::RkMainImpl::RkMainImpl(RkMain *interfaceMain)
        : inf_ptr{interfaceMain}
        , topWindow(nullptr)
        , eventQueue{nullptr}
		, isMainQuit{false}
{
        RK_LOG_INFO("called");
}

RkMain::RkMainImpl::RkMainImpl(RkMain *interfaceMain, int argc, char **argv)
        : inf_ptr{interfaceMain}
        , topWindow(nullptr)
        , eventQueue{nullptr}
		, isMainQuit{false}
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
      auto info = topWindow->nativeWindowInfo();
      if (!info) {
              RK_LOG_ERROR("wring info");
              return false;
      }

#ifdef RK_OS_WIN
      eventQueue = std::make_unique<RkEventQueueWin>();
#elif RK_OS_MAC
#else
      eventQueue = std::make_unique<RkEventQueueX>(info->display);
#endif // RK_WIN_OS
      return true;
}

RkWidget* RkMain::RkMainImpl::topLevelWindow(void)
{
      return topWindow;
}

void RkMain::RkMainImpl::setQuit()
{
	isMainQuit = true;
}

bool RkMain::RkMainImpl::isQuit() const
{
	return isMainQuit;
}

void RkMain::RkMainImpl::processEvents()
{
                auto res = eventQueue->nextEvent();
                if (!res.second)
                        return;

#ifdef RK_OS_WIN				
		        if (!res.first.id && res.second->type() == RkEvent::Type::Close) {
					    setQuit();
				        return;
                }
#endif // RK_OS_WIN

                RkWidget *widget;
                if (res.first.id == topLevelWindow()->id().id)
                        widget = topLevelWindow();
                else
                        widget = topLevelWindow()->child(res.first);

                if (widget)
                        widget->processEvent(res.second);
					
			    if (topLevelWindow()->isClose())
				        setQuit();
        //}
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
		                if (isQuit())
                                break;
                        std::this_thread::sleep_for(std::chrono::milliseconds(15));
                }
        }

        return 0;
}
