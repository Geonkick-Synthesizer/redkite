/**
 * File name: RkQueueWin.cpp
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

#include "RkEventQueueWin.h"
#include "RkLog.h"
#include "RkWidget.h"

RkEventQueueWin::RkEventQueueWin()
{
        RK_LOG_INFO("called");
}

RkEventQueueWin::~RkEventQueueWin()
{
}

bool RkEventQueueWin::pending()
{

        return GetQueueStatus(QS_KEY | QS_HOTKEY
                              | QS_MOUSE | QS_MOUSEBUTTON
                              | QS_MOUSEMOVE | QS_PAINT) != 0;
}

std::pair<RkWindowId, std::shared_ptr<RkEvent>> RkEventQueueWin::nextEvent()
{
        MSG msg;
        if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
                std::shared_ptr<RkEvent> event = nullptr;
                RkWindowId id = rk_id_from_win(msg.hwnd);
                switch (msg.message)
                {
                case WM_PAINT:
                        event = RkEvent::paintEvent();
                        break;
                case WM_KEYDOWN:
                        event = RkEvent::keyPressEvent();
                        break;
                case WM_KEYUP:
                        event = RkEvent::keyReleaseEvent();
                        break;
                case WM_LBUTTONUP:
                case WM_RBUTTONUP:
                case WM_MBUTTONUP:
                        event = RkEvent::buttonPressEvent();
                        break;
                case WM_LBUTTONDOWN:
                case WM_RBUTTONDOWN:
                case WM_MBUTTONDOWN:
                        event = RkEvent::buttonReleaseEvent();
                        break;
                case WM_SIZE:
                        event = RkEvent::resizeEvent();
                        break;
                case WM_QUIT:
                        event = RkEvent::closeEvent();
                        break;
                default:
                        break;
                }

                if (event)
                        return std::make_pair(id, event);
        }

        return {};
}
