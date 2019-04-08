/**
 * File name: RkEvent.h
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

#ifndef RK_EVENT_H
#define RK_EVENT_H

#include "Rk.h"
#include "RkPoint.h"

class RkCloseEvent;
class RkKeyEvent;
class RkMouseEvent;
class RkWheelEvent;
class RkMoveEvent;
class RkResizeEvent;
class RkPaintEvent;
class RkShowEvent;
class RkHideEvent;

class RkEvent {
 public:
        enum class Type: int {
                NoEvent = 0,
                Close = 1,
                KeyPressed = 2,
                KeyReleased = 3,
                MouseMove = 4,
                MouseButtonPress = 5,
                MouseButtonRelease = 6,
                MouseDoubleClick = 7,
                Wheel = 8,
                Move = 9,
                Resize = 10,
                Paint = 11,
                Show = 12,
                Hide = 13
      };

      explicit RkEvent(Type type = Type::NoEvent)
              : eventType{type}
              , eventTime{std::chrono::system_clock::now()} {}
      virtual ~RkEvent() {}

      void setType(Type type) { eventType = type; }
      Type type() const { return eventType; }
      std::chrono::system_clock::time_point time() const { return eventTime; }
      void setTime(const std::chrono::system_clock::time_point &time) {  eventTime = time; }

  private:
      Type eventType;
      std::chrono::system_clock::time_point eventTime;
};

class RkCloseEvent: public RkEvent {
 public:
        RkCloseEvent() : RkEvent(Type::Close) {
	}
};

class RkKeyEvent: public RkEvent {
   public:
        RkKeyEvent(Type type = Type::KeyPressed)
                : RkEvent(type) {}
};

class RkMouseEvent: public RkEvent {
  public:

        enum class ButtonType : int {
                Unknown = 0,
                Left = 1,
                Middle = 2,
                Right = 3,
                WeelUp  = 4,
                WeelDown = 5
        };

      RkMouseEvent(Type type = Type::MouseButtonPress)
              : RkEvent(type)
              , buttonType{ButtonType::Unknown} {}

      int x() const { return mouseCoordinates.x(); }
      void setX(int x) { mouseCoordinates.setX(x); }
      int y() const { return mouseCoordinates.y(); }
      void setY(int x) { mouseCoordinates.setY(x); }
      ButtonType button() const { return buttonType; }
      void setButton(ButtonType type) { buttonType = type; }

 private:
        RkPoint mouseCoordinates;
        ButtonType buttonType;
};

class RkWheelEvent: public RkEvent {
};

class RkMoveEvent: public RkEvent {
};

class RkResizeEvent: public RkEvent {
public:
      RkResizeEvent() : RkEvent(Type::Resize) {
      }
};

class RkPaintEvent: public RkEvent {
 public:
       RkPaintEvent() : RkEvent(Type::Paint) {
       }
};

class RkShowEvent: public RkEvent {
};

class RkHideEvent: public RkEvent {
};

#endif // RK_EVENT_H

