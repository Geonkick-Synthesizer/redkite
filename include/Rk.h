/**
 * File name: Rk.h
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

#ifndef RK_GLOBAL_H
#define RK_GLOBAL_H

#define RK_VERSION 0x010000
#define RK_MAJOR   0x00
#define RK_MINOR   0x00
#define RK_PATCH   0x00

#include <memory>
#include <vector>
#include <string>
#include <list>
#include <memory>
#include <thread>
#include <chrono>
#include <functional>

#define RK_UNUSED(expr) (void)expr

#define RK_DECLARE_IMPL(Class) \
  class Class##Impl; \
  std::shared_ptr<Class##Impl> o_ptr;

#define RK_DELCATE_IMPL_PTR(Class) \
        class Class##Impl; \
        std::shared_ptr<Class##Impl> impl_ptr;

#define RK_DECALRE_INTERFACE_PTR(Class) Class *inf_ptr;

#define RK_CLASS_INFO(name, value) virtual std::string rk_property_ ##name () const { return std::string( #value ); }
#define RK_SET_CLASS_INFO(name, value) virtual std::string rk_property_ ##name () const override { return std::string( #value ); }

#define RK_DISABLE_COPY(Class) \
          Class(const Class &other) = delete; \
          Class& operator=(const Class &other) = delete;

#define RK_DISABLE_MOVE(Class) \
          Class(Class &&other) = delete; \
          Class& operator=(Class &&other) = delete; \

#if defined(RK_OS_WIN) && !defined(RK_FOR_SHARED)
int rkMain(int, char **);
#define main rkMain
#endif // RK_OS_WIN && !RK_FOR_SHARED

#if defined(RK_SINGLE_PRECISION)
using rk_real = float;
#else
using rk_real = double;
#endif // RK_SINGLE_PRECISION

class Rk {
 public:
        Rk() = delete;
        enum class Alignment : int {
                AlignLeft   = 1,
                AlignRight  = 2,
                AlignCenter = 3
        };
};

#define RK_ACT_ARGS(arg, ...) arg, ##__VA_ARGS__
#define RK_ARG_TYPE(type, ...) type, ##__VA_ARGS__
#define RK_ARG_VAL(val, ...) val, ##__VA_ARGS__

#define RK_DECL_ACT(name, prot, type, val) \
        void prot \
        { \
                for (const auto &cb: rk_actions_ ##name ) \
                        cb(val); \
        } \
        void add_action_cb_##name (const std::function<void(type)> &cb) \
        { \
                rk_actions_ ##name.push_back(cb); \
        } \
        std::vector<std::function<void(type)>> rk_actions_ ##name


#define RK_ACT_BIND(obj1, act, act_args, obj2, callback) \
        obj1->add_action_cb_##act ([this](act_args){ obj2->callback; })

#define RK_CALL_ACT(name, args) \
        name(args)

#endif // RK_GLOBAL_H
