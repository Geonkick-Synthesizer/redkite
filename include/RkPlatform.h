#ifndef RK_PLATFORM_H
#define RK_PLATFORM_H

#include "Rk.h"
#include "RkLog.h"

#ifdef RK_OS_WIN
#include <windows.h>
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

std::shared_ptr<RkNativeWindowInfo>
rk_from_native_x11(Display* display, int screenNumber, Window window);

RkWindowId rk_id_from_x11(Window window);

#endif

#endif // RK_PLATFORM_H
