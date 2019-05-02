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
                painter.fillRect(rect(), {150, 150, 150});
        }

        {
                RkPainter painter(this);
                auto r = rect();
                painter.drawText(RkRect(r.left() + 3, r.top() + 3,
                                 r.width() - 6, r.height() - 6), text(),
                                 Rk::Alignment::AlignLeft);
                if (!impl_ptr->isCursorHidden()) {
                        int cursorX = painter.getTextWidth(impl_ptr->textToCursor());
                        painter.drawLine(cursorX + 4, 3, cursorX + 4, height() - 3);
                }
        }
}

void RkLineEdit::keyPressEvent(const std::shared_ptr<RkKeyEvent> &event)
{
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
                impl_ptr->removeText(1, true);
                textEdited(impl_ptr->text());
                return;
        default:
                break;
        }

        std::string str = std::string(1, static_cast<char>(static_cast<int>(event->key())));
        impl_ptr->addText(str);
        textEdited(impl_ptr->text());
        update();
}

void RkLineEdit::keyReleaseEvent(const std::shared_ptr<RkKeyEvent> &event)
{
        RK_UNUSED(event);
}

void RkLineEdit::mouseMoveEvent(const std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkLineEdit::mouseButtonPressEvent(const std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkLineEdit::mouseButtonReleaseEvent(const std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}


