/**
 * File name: RkDialog.h
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

class RK_EXPORT RkDialog : public RkWidget {
 public:
        enum Result : int {
                None = 0,
                Accepted = 1,
                Rejected = 2,
                Closed   = 3
        };

        RkDialog(RkWidget *parent = nullptr);
        virtual ~RkDialog() = default;
        virtual Result wait();
        RK_DECL_ACT(closeDialog,
                    closeDialog(RkDialog::Result result),
                    RK_ARG_TYPE(RkDialog::Result),
                    RK_ARG_VAL(result));

 private:
        RK_DISABLE_COPY(RkDialog)
        RK_DISABLE_MOVE(RkDialog)
};

#endif // RK_DIALOG_H
