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
#include "RkPlatform.h"

class RkEvent;

class RkWidget::RkWidgetXWin {
 public:
        explicit RkWidgetXWin(const std::shared_ptr<RkNativeWindowInfo> &parent = nullptr);
        ~RkWidgetXWin();
        RkWidgetXWin(const RkWidgetXWin &other) = delete;
        RkWidgetXWin& operator=(const RkWidgetXWin &other) = delete;
        RkWidgetXWin(RkWidgetXWin &&other) = delete;
        RkWidgetXWin& operator=(RkWidgetXWin &&other) = delete;
        bool init();
        void show();
        std::shared_ptr<RkNativeWindowInfo> nativeWindowInfo();
        void setTitle(const std::string &title);
        Display* display() { return xDisplay; }
        bool hasParent() const;
        std::pair<int, int> size() const;
        void setSize(const std::pair<int, int> &size);
        int x() const;
        int y() const;
        void setX(int x);
        void setY(int y);
        void addChild(RkWidget *child);
        RkWidget* child(const RkWindowId &id) const;
        RkWindowId id() const;

 protected:
        bool openDisplay();
        bool isWindowCreated() const;

 private:
        std::shared_ptr<RkNativeWindowInfo> parentWindowInfo;
        Display *xDisplay;
        int screenNumber;
        Window xWindow;
        Atom deleteWindowAtom;
        int widgetX;
        int widgetY;
        std::pair<int, int> widgetSize;
        std::list<RkWidget*> widgetChildren;
};

#endif // RK_WIDGET_XWIN_H
