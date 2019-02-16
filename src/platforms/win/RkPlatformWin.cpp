#include "RkPlatform.h"

RkNativeWindowInfo rk_from_native_win(HINSTANCE instance, LPCSTR className, HWND window)
{
        RkNativeWindowInfo info;
        info.instance = instance;
        info.className = className;
        info.window = window;
        return info;
}

RkWindowId rk_id_from_win(HWND window)
{
        RkWindowId id;
        id.id = window;
        return id;
}

