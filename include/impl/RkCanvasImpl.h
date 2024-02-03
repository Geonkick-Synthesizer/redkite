/**
 * File name: RkCanvasImpl.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2024 Iurie Nistor 
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

#ifndef RK_CANVAS_IMPL_H
#define RK_CANVAS_IMPL_H

#include "RkCanvas.h"

class RkCanvasInfo;

class RkCanvas::RkCanvasImpl {
 public:
        explicit RkCanvasImpl(RkCanvas* interface);
        explicit RkCanvasImpl(RkCanvas* interface)
        virtual ~RkCanvasImpl();
        RkCanvasImpl(const RkCanvas &other) = delete;
        RkCanvasImpl& operator=(const RkCanvasImpl &other) = delete;
        RkCanvasImpl(RkCanvasImpl &&other) = delete;
        RkCanvasImpl& operator=(RkCanvasImpl &&other) = delete;
        virtual const RkCanvasInfo* getCanvasInfo() const = 0;
        virtual void freeCanvasInfo() = 0;

 private:
        RK_DECALRE_INTERFACE_PTR(RkCanvas);
};

#endif // RK_CANVAS_IMPL_H
