/**
 * File name: RkLineEdit.h
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

#ifndef RK_LINE_EDIT_H
#define RK_LINE_EDIT_H

#include "RkWidget.h"

class RK_EXPORT RkLineEdit : public RkWidget {
 public:
    RkLineEdit(RkWidget *parent, const std::string &text = std::string());
    virtual ~RkLineEdit() = default;
    void setText(const std::string &text);
    std::string text() const;
    void showCursor();
    void hideCursor();

    RK_DECL_ACT(textEdited, textEdited(const std::string &text), RK_ARG_TYPE(const std::string&), RK_ARG_VAL(text));
    RK_DECL_ACT(enterPressed, enterPressed(), RK_ARG_TYPE(), RK_ARG_VAL());

 protected:
    void paintEvent(const std::shared_ptr<RkPaintEvent> &event) override;
    void keyPressEvent(const std::shared_ptr<RkKeyEvent> &event) override;
    void focusEvent(const std::shared_ptr<RkFocusEvent> &event) override;

    RK_DELCATE_IMPL_PTR(RkLineEdit)
};

#endif // RK_LABEL_H
