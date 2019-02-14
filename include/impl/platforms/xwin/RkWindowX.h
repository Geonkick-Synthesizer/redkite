/**
 * File name: RkWindowX.h
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

#ifndef RK_WINDOW_X_H
#define RK_WINDOW_X_H

#include "Rk.h"
#include "RkPlatform.h"

struct RkWindowId;
struct RkNativeWindowInfo;

class RkWindowX {
 public:
        explicit RkWindowX(const std::shared_ptr<RkNativeWindowInfo> &parent = nullptr);
        explicit RkWindowX(const RkNativeWindowInfo &parent);
        ~RkWindowX();
        RkWindowX(const RkWindowX &other) = delete;
        RkWindowX& operator=(const RkWindowX &other) = delete;
        RkWindowX(RkWindowX &&other) = delete;
        RkWindowX& operator=(RkWindowX &&other) = delete;
        bool init();
        void show();
        std::shared_ptr<RkNativeWindowInfo> nativeWindowInfo();
        void setTitle(const std::string &title);
        Display* display();
        std::pair<int, int> size() const;
        void setSize(const std::pair<int, int> &size);
        std::pair<int, int> position() const;
        void setPosition(const std::pair<int, int> &position);
        RkWindowId id() const;

        void setBackgroundColor(const std::tuple<int, int, int, int> &background);

 protected:
        bool openDisplay();
        bool isWindowCreated() const;
        bool hasParent() const;

 private:
        std::shared_ptr<RkNativeWindowInfo> parentWindowInfo;
        Display *xDisplay;
        int screenNumber;
        Window xWindow;
        Atom deleteWindowAtom;
        mutable std::pair<int, int> windowPosition;
        std::pair<int, int> windowSize;
};

#endif // RK_WIDGET_XWIN_H
