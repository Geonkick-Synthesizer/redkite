/**
 * File name: RkLineEditImpl.cpp
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

#include "RkLineEditImpl.h"
#include "RkPainter.h"
#include "RkLog.h"

RkLineEdit::RkLineEditImpl::RkLineEditImpl(RkLineEdit *interface, RkWidget *parent, const std::string &text)
    : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
    , inf_ptr{interface}
    , editedText{text}
    , cursorIndex{0}
    , selectionIndex{0}
{
}

RkLineEdit::RkLineEditImpl::~RkLineEditImpl()
{
}

void RkLineEdit::RkLineEditImpl::setText(const std::string &text)
{
        editedText = text;
        if (editedText.size() < 1)
                cursorIndex = 0;
        else if (cursorIndex > editedText.size() - 1)
                cursorIndex = editedText.size() - 1;
}

void RkLineEdit::RkLineEditImpl::moveCursorLeft(int n)
{
        if (isSelectionMode()) {
                if (cursorIndex - n < 0)
                        cursorIndex = 0;
                else
                        cursorIndex -= n;
        } else {
                if (selectionIndex - n < 0)
                        selectionIndex = 0;
                else
                        selectionIndex -= n;
        }
}

void RkLineEdit::RkLineEditImpl::moveCursorRight(int n)
{
        if (isSelectionMode()) {
                if (cursorIndex + n > editedText.size() - 1)
                        cursorIndex = editedText.size() - 1;
                else
                        cursorIndex += n;
        else {
                if (selectionIndex + n > editedText.size() - 1)
                        selectionIndex = editedText.size() - 1;
                else
                        selectionIndex += n;
        }
}

void RkLineEdit::RkLineEditImpl::addText(std::string& text)
{
        if (selectionMode()) {
                if (selectionIndex >= cursorIndex) {
                        editedText.replace(cursorIndex, std::abs(selectionIndex - cursorIndex), text);
                        cursorIndex += text.size();
                } else {
                        editedText.replace(selectionIndex, std::abs(selectionIndex - cursorIndex), text);
                        cursorIndex = selectionIndex + text.size();
                }
                selectionIndex = cursorIndex;
        } else {
                editedText.insert(cursorIndex, text);
                cursorIndex += text.size();
        }
}

void RkLineEdit::RkLineEditImpl::removeText(int n, bool after)
{
        if (selectionMode())
                n = std::abs(selectionIndex - cursorIndex);
                
        if (after) {
                if (cursorIndex + n > editedText.size() - 1)
                        editedText.erase(cursorIndex, editedText.size() - 1);
                else
                        editedText.erase(cursorIndex, n);
        } else {
                if (cursorIndex - n < 0) {
                        editedText.erase(0, cursorIndex);
                        cursorIndex = 0;
                } else {
                        editedText.erase(cursorIndex - n, cursorIndex);
                        cursorIndex -= n;
                }       
        }

        if (selectionMode())
                selectionIndex = cursorIndex;
}

std::string RkLineEdit::RkLineEditImpl::text() const
{
        return editedText;
}
