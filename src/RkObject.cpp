/**
 * File name: RkObject.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor
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

#include "RkObject.h"
#include "RkLog.h"

RkObject::RkObject(RkObject *parent)
{
        RK_UNUSED(parent);
}

RkObject::~RkObject()
{
        // Remove myself from bound objects.
        for (auto obj: rk_bound_objects)
                obj->rk_remove_object_observers(this);
        rk_bound_objects.clear();

        // Remove myself from the observers objects.
        for (auto o: rk_observers_list) {
                if (o->object())
                        o->object()->rk_remove_bound_object(this);
                delete o;
        }
        rk_observers_list.clear();
}

void RkObject::rk_add_observer(RkObserver *observer)
{
        rk_observers_list.push_back(observer);
}

void RkObject::rk_remove_object_observers(RkObject *obj)
{
        rk_observers_list.erase(std::remove_if(rk_observers_list.begin(),
                                               rk_observers_list.end(),
                                               [obj](RkObserver *o)  {
                                                       if (o->object() == nullptr) {
                                                               return false;
                                                       } else if(o->object() == obj) {
                                                               delete o;
                                                               return true;
                                                       }
                                                       return false;
                                               }),
                                rk_observers_list.end());
}

std::vector<RkObserver*>& RkObject::rk_get_observers()
{
        return rk_observers_list;
}

void RkObject::rk_add_bound_object(RkObject *obj)
{
        auto res = std::find(std::begin(rk_bound_objects), std::end(rk_bound_objects), obj);
        if (res != std::end(rk_bound_objects))
                return;
}

void RkObject::rk_remove_bound_object(RkObject *obj)
{
        rk_bound_objects.erase(std::remove_if(rk_bound_objects.begin(),
                                              rk_bound_objects.end(),
                                              [obj](RkObject *o)  {
                                                      if (o == obj)
                                                              return true;
                                                      return false;
                                              }),
                               rk_bound_objects.end());
}

