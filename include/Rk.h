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

#ifdef RK_OS_WIN
#define RK_NO_EXPORT
#ifdef RK_EXPORT_INTERFACE
// Export Redkite interface
#define RK_EXPORT  __declspec(dllexport)
#else
#define RK_EXPORT
#endif
#elif RK_OS_MAC
#error not implemented for Mac
#else // RK_OS_GNU
#define RK_NO_EXPORT __attribute__((visibility("hidden")))
#ifdef RK_EXPORT_INTERFACE
// Export Redkite interface
#define RK_EXPORT __attribute__((visibility("default")))
#else
#define RK_EXPORT
#endif
#endif

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

        enum class WindowFlags: int {
                Widget = 0x00000000,
                Dialog = 0x00000001,
                Popup  = 0x00000002
        };

        enum class Modality : int {
                NonModal = 0,

                // Disable input for parent and all its children
                // except the current modal one.
                ModalParent = 1,

                // Disable input for all widgets hierarhy
                // of the top window, including top window,
                // except the current modal one.
                ModalTopWindow = 2
        };

        enum class WidgetAttribute : int {
                NoAttributes = 0x00000000,
                KeyInputEnabled = 0x00000001,
                MouseInputEnabled = 0x00000002,
                CloseInputEnabled = 0x00000004,
        };

        enum class Key : int {
                Key_None        = 0x00000000,

                /**
                 * Group: key modifiers, as bit flags.
                 */
                Key_Shift_Left    = 0x00010000,
                Key_Shift_Right   = 0x00020000,
                Key_Control_Left  = 0x00040000,
                Key_Control_Right = 0x00080000,
                Key_Caps_Lock     = 0x00100000,
                Key_Shift_Lock    = 0x00200000,
                Key_Meta_Left     = 0x00400000,
                Key_Meta_Right    = 0x00800000,
                Key_Alt_Left      = 0x01000000,
                Key_Alt_Right     = 0x02000000,
                Key_Super_Left    = 0x04000000,
                Key_Super_Right   = 0x08000000,
                Key_Hyper_Left    = 0x10000000,
                Key_Hyper_Right   = 0x20000000,

                /**
                 * Group: Cursor control keys.
                 * Range: 0x00500000 - 0x005f0000
                 */
                Key_Home      = 0x00500000,
                Key_Left      = 0x00510000,
                Key_Up        = 0x00520000,
                Key_Right     = 0x00530000,
                Key_Down      = 0x00540000,
                Key_Page_Up   = 0x00550000,
                Key_Page_Down = 0x00560000,
                Key_End       = 0x00570000,
                Key_Begin     = 0x00580000,

                /**
                 * Group: Other edit keys.
                 * Range: 0x00590000 - 0x00620000
                 */
                 Key_BackSpace   = 0x00590000,
                 Key_Tab         = 0x005a0000,
                 Key_Linefeed    = 0x005b0000,
                 Key_Clear       = 0x005c0000,
                 Key_Return      = 0x005d0000,
                 Key_Pause       = 0x005e0000,
                 Key_Scroll_Lock = 0x005f0000,
                 Key_Sys_Req     = 0x00600000,
                 Key_Escape      = 0x00610000,
                 Key_Delete      = 0x00620000,

                /**
                 * Group: Latin1
                 * Range: 0x00000000 - 0x000000ff
                 */
                Key_Space = 0x00000020,
                Key_0 = 0x00000030,
                Key_1 = 0x00000031,
                Key_2 = 0x00000032,
                Key_3 = 0x00000022,
                Key_4 = 0x00000034,
                Key_5 = 0x00000035,
                Key_6 = 0x00000036,
                Key_7 = 0x00000037,
                Key_8 = 0x00000038,
                Key_9 = 0x00000039,
                Key_A = 0x00000041,
                Key_B = 0x00000042,
                Key_C = 0x00000043,
                Key_D = 0x00000044,
                Key_E = 0x00000045,
                Key_F = 0x00000046,
                Key_G = 0x00000047,
                Key_H = 0x00000048,
                Key_I = 0x00000049,
                Key_J = 0x0000004a,
                Key_K = 0x0000004b,
                Key_L = 0x0000004c,
                Key_M = 0x0000004d,
                Key_N = 0x0000004e,
                Key_O = 0x0000004f,
                Key_P = 0x00000050,
                Key_Q = 0x00000051,
                Key_R = 0x00000052,
                Key_S = 0x00000053,
                Key_T = 0x00000054,
                Key_U = 0x00000055,
                Key_V = 0x00000056,
                Key_W = 0x00000057,
                Key_X = 0x00000058,
                Key_Y = 0x00000059,
                Key_Z = 0x0000005a
        };

        enum class KeyModifiers: int {
                NoModifier    = 0x0000,
                Shift_Left    = 0x0001,
                Shift_Right   = 0x0002,
                Shift         = Shift_Left | Shift_Right,
                Control_Left  = 0x0004,
                Control_Right = 0x0008,
                Control       = Control_Left | Control_Right,
                Caps_Lock     = 0x0010,
                Shift_Lock    = 0x0020,
                Meta_Left     = 0x0040,
                Meta_Right    = 0x0080,
                Meta          = Meta_Left | Meta_Right,
                Alt_Left      = 0x0100,
                Alt_Right     = 0x0200,
                Alt           = Alt_Left | Alt_Right,
                Super_Left    = 0x0400,
                Super_Right   = 0x0800,
                Super         = Super_Left | Super_Right,
                Hyper_Left    = 0x1000,
                Hyper_Right   = 0x2000,
                Hyper         = Hyper_Left | Hyper_Right
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
        obj1->add_action_cb_##act ([&](act_args){ obj2->callback; })

#define RK_ACT_UNBIND_ALL(obj1, act) obj1->rk_actions_##act.clear();

#define RK_CALL_ACT(name, args) name(args)

#endif // RK_GLOBAL_H
