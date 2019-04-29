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

#include "RkLabel.h"
#include "RkLabelImpl.h"
#include "RkLog.h"

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
}

void RkLineEdit::keyPressEvent(const std::shared_ptr<RkKeyEvent> &event)
{
        impl_ptr->enableSelectionMode(event->modifiers() & Rk::KeyModifier::Shift);
        switch (event->key())
        {
        case Rk::Key::Left:
                impl_ptr->moveCursorLeft(1);
                break;
        case Rk::Key::Right:
                impl_ptr->moveCursorRight(1);
                break;
        case Rk::Key::Backspace:
                impl_ptr->removeText(1, false);
                break;
        case Rk::Key::Delete:
                impl_ptr->removeText(1, true);
                break;

        }
        
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

