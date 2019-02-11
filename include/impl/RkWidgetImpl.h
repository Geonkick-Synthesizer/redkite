/**
 * File name: RkWidgetImpl.h
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

#ifndef RK_WIDGET_IMPL_H
#define RK_WIDGET_IMPL_H

#include "RkWidget.h"

//#ifdef RK_WIN_OS
//#elif RK_MAC_OS
//#else
//class RkWidgetXWin;
//#endif

class RkWidget::RkWidgetImpl {
 public:
        explicit RkWidgetImpl(RkWidget* interface, RkWidget* parent = nullptr);
        explicit RkWidgetImpl(RkWidget* interface, const RkNativeWindowInfo &parent);
        RkWidgetImpl(const RkWidget &other) = delete;
        RkWidgetImpl& operator=(const RkWidgetImpl &other) = delete;
        RkWidgetImpl(RkWidgetImpl &&other) = delete;
        RkWidgetImpl& operator=(RkWidgetImpl &&other) = delete;
        virtual ~RkWidgetImpl() = default;

        void show();
        void setTitle(const std::string &title);
        const std::string& title() const;
        std::shared_ptr<RkNativeWindowInfo> nativeWindowInfo() const;
        bool isClose() const;
        void processEvents();
        RkWindowId id() const;
        void processEvent(const std::shared_ptr<RkEvent> &event);
        RkWidget* parent() const;
        RkWidget* child(const RkWindowId &id) const;
        void addChild(const RkWidget* child);

        void setSize(int x, int y);
        void setSize(const std::pair<int, int> &size);
        std::pair<int, int> size() const;
        void setWidth(int w);
        int width() const;
        void setHeight(int h);
        int height() const;
        int x() const;
        void setX(int x);
        int y() const;
        void setY(int y);
        //          void setBackgroundColor(const RkColor &color);
        void setBackgroundColor(int r, int g, int b);
        //void setBackgroundColor(std::tuple<int, int, int, int> &color);
        //RkColor backgroundColor() const;
        //        std::tuple<int, int, int, int> backgroundColor() const;

 private:
        // Declare pointer to the interface class RkWidget.
        RK_DECALRE_INTERFACE_PTR(RkWidget)
        RkWidget *parentWidget;
        //#ifdef RK_WIN_OS
        //std::unique_ptr<RkWidgetWin> platformWindow;
        //#elif
        //std::unique_ptr<RkWidgetMac> platformWindow;
        //#else
        //        std::unique_ptr<RkWidgetXWin> platformWindow;
        //#endif
        std::string widgetTitle;
        std::list<RkWidget*> widgetChildren;
        bool widgetClosed;
};

#endif // RK_WIDGET_IMPL_H
