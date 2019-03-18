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

class RkEventQueue;

#ifdef RK_OS_WIN
class RkWindowWin;
#elif RK_OS_MAC
#else
class RkWindowX;
#endif // RK_WIN_OS

class RkWidget::RkWidgetImpl {
 public:
        explicit RkWidgetImpl(RkWidget* interface, RkWidget* parent = nullptr);
        explicit RkWidgetImpl(RkWidget* interface, const RkNativeWindowInfo &parent);
        RkWidgetImpl(const RkWidget &other) = delete;
        RkWidgetImpl& operator=(const RkWidgetImpl &other) = delete;
        RkWidgetImpl(RkWidgetImpl &&other) = delete;
        RkWidgetImpl& operator=(RkWidgetImpl &&other) = delete;
        virtual ~RkWidgetImpl();

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
        void addChild(RkWidget* child);

        void setSize(const std::pair<int, int> &size);
        std::pair<int, int> size() const;
        int minimumWidth() const;
        int maximumWidth() const;
        int minimumHeight() const;
        int maximumHeight() const;

        void setPosition(const std::pair<int, int> &position);
        std::pair<int, int> position() const;
        void setBorderWidth(int width);
        void setBorderColor(const std::tuple<int, int, int> &color);
        void setBackgroundColor(const std::tuple<int, int, int> &background);
        void setEventQueue(RkEventQueue* queue);
        RkEventQueue* getEventQueue();

        void setLayout(RkLayout *layout);
        RkLayout* layout() const;

 private:
        RK_DECALRE_INTERFACE_PTR(RkWidget)
        RkWidget *parentWidget;
#ifdef RK_OS_WIN
        std::unique_ptr<RkWindowWin> platformWindow;
#elif RK_OS_MAC
#else
        std::unique_ptr<RkWindowX> platformWindow;
#endif // RK_WIN_OS
        std::string widgetTitle;
        std::list<RkWidget*> widgetChildren;
        bool widgetClosed;
        RkEventQueue* eventQueue;
        RkLayout *widgetLayout;
};

#endif // RK_WIDGET_IMPL_H
