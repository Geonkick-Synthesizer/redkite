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
#include "RkTimer.h"

RkLineEdit::RkLineEditImpl::RkLineEditImpl(RkLineEdit *interface, RkWidget *parent, const std::string &text)
    : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
    , inf_ptr{interface}
    , editedText{text}
    , cursorIndex{0}
    , selectionIndex{0}
    , isSelectionMode{false}
    , cursorTimer{std::make_unique<RkTimer>(500, parent->eventQueue())}
    , isShowCursor{hasFocus()}
    , lastCahnges{std::chrono::system_clock::now()}
{
        RK_ACT_BIND(cursorTimer.get(), timeout, RK_ACT_ARGS(), this, onCursorTimeout());
        hasFocus() ? showCursor(true) : showCursor(false);
}

RkLineEdit::RkLineEditImpl::~RkLineEditImpl()
{
        cursorTimer->stop();
}

void RkLineEdit::RkLineEditImpl::setText(const std::string &text)
{
        editedText = text;
        if (editedText.size() < 1)
                cursorIndex = 0;
        else if (cursorIndex > editedText.size() - 1)
                cursorIndex = editedText.size() - 1;
        lastCahnges = std::chrono::system_clock::now();
}

void RkLineEdit::RkLineEditImpl::moveCursorLeft(int n)
{
        if (editedText.empty()) {
                cursorIndex = 0;
        } else if (isSelectionMode) {
        } else {
                cursorIndex -= n;
                if (cursorIndex < 0)
                        cursorIndex = 0;
        }
        lastCahnges = std::chrono::system_clock::now();
}

void RkLineEdit::RkLineEditImpl::moveCursorRight(int n)
{
        if (editedText.empty()) {
                cursorIndex = 0;
        } else if (isSelectionMode) {
        } else {
                cursorIndex += n;
                if (cursorIndex > editedText.size() - 1)
                        cursorIndex = editedText.size();
        }
        lastCahnges = std::chrono::system_clock::now();
}

void RkLineEdit::RkLineEditImpl::addText(const std::string& text)
{
        if (isSelectionMode) {
        } else {
                if (cursorIndex == editedText.size())
                        editedText += text;
                else
                        editedText.insert(cursorIndex, text);
                cursorIndex += text.size();
        }
        lastCahnges = std::chrono::system_clock::now();
}

void RkLineEdit::RkLineEditImpl::removeText(int n, bool after)
{
        if (editedText.size() < 1)
                return;

        if (after) {
                if (static_cast<decltype(editedText.size())>(cursorIndex + n) > editedText.size())
                        editedText.erase(cursorIndex, editedText.size() - 1);
                else
                        editedText.erase(cursorIndex, n);
        } else if (cursorIndex > 0) {
                if (cursorIndex - n < 0) {
                        editedText.erase(editedText.begin(), editedText.begin() + cursorIndex);
                        cursorIndex = 0;
                } else {
                        editedText.erase(cursorIndex - n, n);
                        cursorIndex -= n;
                }
        }

        if (isSelectionMode)
                selectionIndex = cursorIndex;
        lastCahnges = std::chrono::system_clock::now();
}

std::string RkLineEdit::RkLineEditImpl::text() const
{
        return editedText;
}

std::string RkLineEdit::RkLineEditImpl::textToCursor() const
{
        if (editedText.empty())
                return std::string();
        else
                return editedText.substr(0, cursorIndex);
}

void RkLineEdit::RkLineEditImpl::enableSelectionMode(bool b)
{
        isSelectionMode = b;
}

bool RkLineEdit::RkLineEditImpl::isCursorHidden() const
{
        return !isShowCursor;
}

void RkLineEdit::RkLineEditImpl::onCursorTimeout()
{
        if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - lastCahnges).count() > 1000) {
                isShowCursor = !isShowCursor;
                inf_ptr->update();
        }
}

void RkLineEdit::RkLineEditImpl::showCursor(bool b)
{
        isShowCursor = b;
        isShowCursor ? cursorTimer->start() : cursorTimer->stop();
}
