/**
 * File name: RkPlatform.h
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

#ifndef RK_PLATFORM_H
#define RK_PLATFORM_H

#include "Rk.h"
#include "RkLog.h"

#ifdef RK_OS_WIN
#define WINVER 0x0501

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

struct RkWindowId {
    RkWindowId(HWND arg = nullptr) : id(arg) {}
    HWND id;
};

struct RkNativeWindowInfo {
        RkNativeWindowInfo(HWND arg = nullptr) : window(arg) {}
        HWND window;
};

//RkNativeWindowInfo rk_from_native_win(HWND window);
//RkWindowId rk_id_from_win(HWND window);

#elif RK_OS_MAC
// to be defined
#else
#include <X11/Xlib.h>

struct RkWindowId {
        Window id;
};

struct RkNativeWindowInfo
{
        Display* display;
        int screenNumber;
        Window window;
};

RkNativeWindowInfo rk_from_native_x11(Display* display, int screenNumber, Window window);
RkWindowId rk_id_from_x11(Window window);

#endif

#endif // RK_PLATFORM_H
