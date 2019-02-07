/**
 * File name: RkWidgetXWin.h
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

#ifndef RK_WIDGET_XWIN_H
#define RK_WIDGET_XWIN_H

#include "RkWidget.h"

#ifdef RK_OS_WIN
#include <windows.h>
#elif RK_OS_MAC
 // to be defined
#else
#include <X11/Xlib.h>
#endif

class RkEvent;

class RkWidget::RkWidgetXWin {
 public:
        explicit RkWidgetXWin(RkNativeWindow parent = 0);
        ~RkWidgetXWin();
        RkWidgetXWin(const RkWidgetXWin &other) = delete;
        RkWidgetXWin& operator=(const RkWidgetXWin &other) = delete;
        RkWidgetXWin(RkWidgetXWin &&other) = delete;
        RkWidgetXWin& operator=(RkWidgetXWin &&other) = delete;
        bool init();
        void show();
        RkWidget::RkNativeWindow getWindow();
        void setTitle(const std::string &title);
        Display* display() { return xDisplay; }
        std::list<std::shared_ptr<RkEvent>> getEvents();

 private:
        RkNativeWindow xParent;
        Display *xDisplay;
        int screenNumber;
        Window xWindow;
        Atom deleteWindowAtom;
};

#endif // RK_WIDGET_XWIN_H
