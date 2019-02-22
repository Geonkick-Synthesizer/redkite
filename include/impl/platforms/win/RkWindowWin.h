/**
 * File name: RkWindowWin.h
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

#ifndef RK_WINDOW_WIN_H
#define RK_WINDOW_WIN_H

#include "Rk.h"
#include "RkPlatform.h"

class RkEventQueue;

class RkWindowWin {
 public:
        explicit RkWindowWin(const std::shared_ptr<RkNativeWindowInfo> &parent = nullptr);
        explicit RkWindowWin(const RkNativeWindowInfo &parent);
        ~RkWindowWin();
        RkWindowWin(const RkWindowWin &other) = delete;
        RkWindowWin& operator=(const RkWindowWin &other) = delete;
        RkWindowWin(RkWindowWin &&other) = delete;
        RkWindowWin& operator=(RkWindowWin &&other) = delete;
        bool init();
        void show();
        std::shared_ptr<RkNativeWindowInfo> nativeWindowInfo();
        void setTitle(const std::string &title);
        std::pair<int, int> size() const;
        void setSize(const std::pair<int, int> &size);
        std::pair<int, int> position() const;
        void setPosition(const std::pair<int, int> &position);
        RkWindowId id() const;

        void setBorderWidth(int width);
        void setBorderColor(const std::tuple<int, int, int> &color);
        void setBackgroundColor(const std::tuple<int, int, int> &background);
        void setEventQueue(const std::shared_ptr<RkEventQueue> &queue);

 protected:
        bool isWindowCreated() const;
        bool hasParent() const;
        //        unsigned long pixelValue(const std::tuple<int, int, int> &color);

 private:
        std::shared_ptr<RkNativeWindowInfo> parentWindowInfo;
        RkWindowId windowHandle;
        mutable std::pair<int, int> windowPosition;
        std::pair<int, int> windowSize;
        int borderWidth;
        std::tuple<int, int, int> borderColor;
        std::tuple<int, int, int> backgroundColor;
        std::shared_ptr<RkEventQueue> eventQueue;
};

#endif // RK_WIDGET_WIN_H
