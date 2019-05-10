/**
 * File name: RkLineEdit.cpp
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

#include "RkLineEdit.h"
#include "RkLineEditImpl.h"
#include "RkLog.h"
#include "RkEvent.h"
#include "RkPainter.h"

RkLineEdit::RkLineEdit(RkWidget *parent, const std::string &text)
        : RkWidget(parent, std::static_pointer_cast<RkWidget::RkWidgetImpl>(std::make_shared<RkLineEdit::RkLineEditImpl>(this, parent, text)))
        , impl_ptr{std::static_pointer_cast<RkLineEdit::RkLineEditImpl>(o_ptr)}
{
}

void RkLineEdit::setText(const std::string &text)
{
     impl_ptr->setText(text);
     update();
}

std::string RkLineEdit::text() const
{
     return impl_ptr->text();
}

void RkLineEdit::paintEvent(const std::shared_ptr<RkPaintEvent> &event)
{
        RK_UNUSED(event);

        {
                RkPainter painter(this);
                painter.fillRect(rect(), background());
        }

        {
                RkPainter painter(this);
                painter.setFont(font());

                // Draw selection background.
                if (impl_ptr->selectionMode()) {
                        auto text = impl_ptr->getText(0, impl_ptr->selectionStart());
                        int xpos = painter.getTextWidth(text);
                        int nSelectedChars = impl_ptr->selectionEnd() - impl_ptr->selectionStart();
                        text = impl_ptr->getText(impl_ptr->selectionStart(), nSelectedChars);
                        int w = painter.getTextWidth(text);
                        painter.fillRect(RkRect(4 + xpos, 2, w, height() - 4) , {52, 116, 209});
                }

                // Draw edited text.
                auto pen = painter.pen();
                pen.setColor(textColor());
                painter.setPen(pen);
                painter.drawText(4, rect().top() + (height() - font().size()) / 2 + font().size() - height() / 8, text());

                // Draw cursor.
                pen = painter.pen();
                pen.setColor(color());
                painter.setPen(pen);
                if (!impl_ptr->isCursorHidden()) {
                        int cursorX = painter.getTextWidth(impl_ptr->textToCursor());
                        painter.drawLine(cursorX + 4, 3, cursorX + 4, height() - 4);
                }
        }
}

/**
 * [OK] Left
 * Shift+Left
 * [OK] Right Arrow
 * Shift+Right Arrow
 * Home
 * End
 * [OK] Backspace
 * Ctrl+Backspace
 * [OK] Delete
 * Ctrl+Delete
 * [OK] Ctrl+A
 * Ctrl+C
 * Ctrl+Insert
 * Ctrl+K
 * Ctrl+V
 * Shift+Insert
 * Ctrl+X
 * Shift+Delete
 * Ctrl+Z
 * Ctrl+Y
 */
void RkLineEdit::keyPressEvent(const std::shared_ptr<RkKeyEvent> &event)
{
        if (!hasFocus())
                return;

        showCursor();
        switch (event->key())
        {
        case Rk::Key::Key_Left:
                impl_ptr->moveCursorLeft(1);
                return;
        case Rk::Key::Key_Right:
                impl_ptr->moveCursorRight(1);
                return;
        case Rk::Key::Key_BackSpace:
                impl_ptr->removeText(1, false);
                textEdited(impl_ptr->text());
                return;
        case Rk::Key::Key_Delete:
                if (impl_ptr->selectionMode())
                        impl_ptr->deleteSelection();
                else
                        impl_ptr->removeText(1, true);
                textEdited(impl_ptr->text());
                update();
                return;
        case Rk::Key::Key_Return:
                action enterPressed();
                return;
        case Rk::Key::Key_a:
        case Rk::Key::Key_A:
                if (event->modifiers() & static_cast<int>(Rk::KeyModifiers::Control)) {
                        impl_ptr->selectAll();
                        update();
                        return;
                }
                break;
        case Rk::Key::Key_Control_Left:
        case Rk::Key::Key_Control_Right:
                return;
        default:
                break;
        }

        std::string str = std::string(1, static_cast<char>(static_cast<int>(event->key())));
        impl_ptr->addText(str);
        textEdited(impl_ptr->text());
        update();
}

void RkLineEdit::focusEvent(const std::shared_ptr<RkFocusEvent> &event)
{
        RK_UNUSED(event);
        RK_LOG_DEBUG("setFocus [" << title() << "]: " << (event->type() == RkEvent::Type::FocusedIn));
        setFocus(event->type() == RkEvent::Type::FocusedIn);
        hasFocus() ? showCursor() : hideCursor();
}

void RkLineEdit::showCursor()
{
        impl_ptr->showCursor(true);
        update();
}

void RkLineEdit::hideCursor()
{
        impl_ptr->showCursor(false);
        update();
}
