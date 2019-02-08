/**
 * File name: RkLabelImpl.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://quamplex.com>
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

#define RK_LABEL_IMPL_H
#define RK_LABEL_IMPL_H

#include "RKWidgetImpl.h"

class RkLabelImpl : public RkWidget::RkWidgetImpl {
 public:
    RkLabelImpl(RkLabel *interface, const std::string &text = std::string());
    ~RkLabelImpl();
    void setText(std:string &text);
    std::string text() const;

 private:
    RK_DECALRE_INTERFACE_PTR(RkLabel)
    RK_DELCATE_IMPL_PTR(RkLabelImpl)
    std::string labelText;
};

#endif // RK_LABEL_H
