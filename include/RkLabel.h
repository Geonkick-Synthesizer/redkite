/**
 * File name: RkLabel.h
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

#ifndef RK_LABEL_H
#define RK_LABEL_H

#include "RkWidget.h"
//#include "RkImage.h"

class RkLabel : public RkWidget {
 public:
    RkLabel(RkWidget *parent = nullptr);
    RkLabel(const std::string &text, RkWidget *parent = nullptr);
    virtual ~RkLabel() = default;
    void setText(const std::string &text);
    std::string text() const;
    void setImage(const std::string &file);
    void setImage(const RkImage &image);

 protected:
    RK_DELCATE_IMPL_PTR(RkLabel)
    virtual void paintEvent(const std::shared_ptr<RkPaintEvent> &event) override;
};

#endif // RK_LABEL_H
