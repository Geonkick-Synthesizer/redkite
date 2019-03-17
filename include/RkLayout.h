/**
 * File name: RkLayout.h
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

#ifndef RK_LAYOUT_H
#define RK_LAYOUT_H

#include "Rk.h"
#include "RkWidget.h"

class RkLayout {
 public:
          RkLayout(RkWidget *parent = nullptr);
          virtual ~RkLayout();
          void setPadding(int padding);
          int padding() const;
          virtual void update() = 0;

 protected:
          RK_DECLARE_IMPL(RkLayout)
          RkLayout(RkWidget *parent, const std::shared_ptr<RkLayoutImpl> &impl);

 private:
          RK_DISABLE_COPY(RkLayout)
          RK_DISABLE_MOVE(RkLayout)
};

#endif // RK_LAYOUT_H
