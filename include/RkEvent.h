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
	   None,
           Close,
	   KeyPress,
	   KeyRelease,
	   MouseMove,
	   MouseButtonPress,
	   MouseButtonRelease,
           MouseDoubleClick,
	   Wheel,
	   Move,
           Resize,
           Paint,
           Show,
           Hide
      };

      RkEvent(Type type = Type::None) : eventType(type) {}
      virtual ~RkEvent() {}

      void setType(Type type) { eventType = type; }
      Type type() const { return eventType; }

      static std::shared_ptr<RkPaintEvent> paintEvent() { return std::move(std::make_shared<RkPaintEvent>()) ;}
      static std::shared_ptr<RkKeyEvent> keyPressEvent() { return std::move(std::make_shared<RkKeyEvent>()) ;}
      static std::shared_ptr<RkKeyEvent> keyReleaseEvent() { return std::move(std::make_shared<RkKeyEvent>(Type::KeyRelease)) ;}
      static std::shared_ptr<RkMouseEvent> buttonPressEvent() { return std::move(std::make_shared<RkMouseEvent>()) ;}
      static std::shared_ptr<RkMouseEvent> buttonReleaseEvent() { return std::move(std::make_shared<RkMouseEvent>(Type::MouseButtonRelease)) ;}
      static std::shared_ptr<RkCloseEvent> closeEvent() { return std::move(std::make_shared<RkCloseEvent>()) ;}
      static std::shared_ptr<RkResizeEvent> resizeEvent() { return std::move(std::make_shared<RkResizeEvent>()) ;}

  private:
      //      RK_PRIVATE_IMPL(RkEventPrivate, privateEvent)
      Type eventType;
};

class RkCloseEvent: public RkEvent {
 public:
        RkCloseEvent() : RkEvent(Type::Close) {
	}
};

class RkKeyEvent: public RkEvent {
   public:
        RkKeyEvent(Type type = Type::KeyPress)
	    : RkEvent(type  == Type::KeyPress ? Type::KeyPress : Type::KeyRelease) {
	}
};

class RkMouseEvent: public RkEvent {
  public:
      RkMouseEvent(Type type = Type::MouseButtonPress)
              : RkEvent(type == Type::MouseMove || type == Type::MouseButtonPress ||
                        type == Type::MouseButtonRelease ||
                        type == Type::MouseDoubleClick ? type : Type::MouseButtonPress) {
      }
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

