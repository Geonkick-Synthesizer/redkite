/**
 * File name: RkLineEditImpl.h
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

#ifndef RK_LINE_EDIT_IMPL_H
#define RK_LINE_EDIT_IMPL_H

#include "RkLineEdit.h"
#include "RkWidgetImpl.h"

class RkLineEdit::RkLineEditImpl : public RkWidget::RkWidgetImpl {
 public:
        RkLineEditImpl(RkLineEdit *interface,  RkWidget *parent = nullptr, const std::string &text = std::string());
        virtual ~RkLineEditImpl();
        void setText(const std::string &text);
        void addText(const std::string& text);
        void removeText(int n, bool after);
        std::string text() const;
        void moveCursorRight(int n = 1);
        void moveCursorLeft(int n = 1);
        void enableSelectionMode(bool b);

 private:
    RK_DECALRE_INTERFACE_PTR(RkLineEdit)
    std::string editedText;
    int cursorIndex;
    int selectionIndex;
    bool isSelectionMode;
};

#endif // RK_LABEL_H
